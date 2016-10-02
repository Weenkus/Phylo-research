#include <iostream>
#include <string>
#include <unordered_map>
#include <omp.h>
#include <time.h>
#include <fstream>

#include <stdio.h>
#include <string.h>

#include "Utils/FastaParser.h"
#include "SimHash.h"
#include "Utils/Help.h"
#include "Utils/AlphabetReduction.h"
#include "HashFunctions/Blash/Blash.h"


using namespace std;

const int MIN_NUM_OF_ARUGMENTS{3};

bool is_valid_user_input(int argc);
void invalid_number_of_arguments_print(int argc, char *argv[]);
void SimHash_start(int argc, char **argv);


int main(int argc, char *argv[]) {
    if (is_valid_user_input(argc)) {
        invalid_number_of_arguments_print(argc, argv);
    } else {
        SimHash_start(argc, argv);
        return 0;
    }
}


bool is_valid_user_input(int argc) {
    return argc < MIN_NUM_OF_ARUGMENTS;
}


void invalid_number_of_arguments_print(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "help") == 0 || strcmp(argv[i], "-help") == 0) {
            Help::print();
            exit(0);
        }
    }

    cerr << "Invalid number of arguments." << endl;
    cout << "Type help for more information" << endl;
    exit(0);
}


void SimHash_start(int argc, char **argv) {
    char *input_file_path {nullptr},
            *hash{nullptr},
            *output_file_path{nullptr},
            *score_matrix_path{nullptr},
            *alphabet_reduction_file_path{nullptr};

    int num_threads {1},
            mutation_threshold{0},
            blash_threshold{0};

    size_t sliding_window_size{8};
    SimHash::HashAlgorithm hash_algorithm = SimHash::HashAlgorithm::Native;  // Default hash functions

    std::cout << argv[0] << " ";
    for (int i = 1; i < argc; i++) {
        if (i + 1 != argc) {
            if (strcmp(argv[i], "-num_threads") == 0) {
                num_threads = atoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-in") == 0) {
                input_file_path = argv[i + 1];
            } else if (strcmp(argv[i], "-out") == 0) {
                output_file_path = argv[i + 1];
            } else if (strcmp(argv[i], "-score_matrix") == 0) {
                score_matrix_path = argv[i + 1];
            } else if (strcmp(argv[i], "-alphabet_reduction") == 0) {
                alphabet_reduction_file_path = argv[i + 1];
            } else if (strcmp(argv[i], "-hash") == 0) {

                hash = argv[i + 1];
                if (strcmp(hash, "Native") == 0) {
                    hash_algorithm = SimHash::HashAlgorithm::Native;
                } else if (strcmp(hash, "Boost") == 0) {
                    hash_algorithm = SimHash::HashAlgorithm::Boost;
                } else if (strcmp(hash, "Spooky") == 0) {
                    hash_algorithm = SimHash::HashAlgorithm::Spooky;
                } else if (strcmp(hash, "Blash") == 0) {
                    hash_algorithm = SimHash::HashAlgorithm::BlosumHash;
                } else {
                    cerr << endl << endl << "Hashing algorithm " << hash << " doesn't exists." << endl;
                    exit(0);
                }

            } else if (strcmp(argv[i], "-sliding_window") == 0) {
                sliding_window_size = static_cast<size_t >(atoi(argv[i + 1]));
            } else if (strcmp(argv[i], "-mutation_threshold") == 0) {
                mutation_threshold = atoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-blash_threshold") == 0) {
                blash_threshold = atoi(argv[i + 1]);
            }
        }
        cout << argv[i] << " ";
    }

    // Print program atributes
    cout << endl << endl;
    if(input_file_path != nullptr)
        cout << "Input file: " << input_file_path << endl;
    if(output_file_path != nullptr )
        cout << "Output file: " << output_file_path << endl;

    cout << "Hash function: " << hash << endl;
    cout << "Number of threads: " << num_threads << endl;
    cout << "Sliding window length: " << sliding_window_size << endl;
    cout << "Mutation threshold: " << mutation_threshold << endl;
    cout << "Blash threshold: " << blash_threshold << endl << endl;

    ofstream output_file_handle(output_file_path);

    // Parse input file
    double start = clock();
    unordered_map<string, string> sequence_id_map = FastaParser::parse_fasta_file(input_file_path);
    cout << "\nFast file parsing done in " << (clock()-start)/CLOCKS_PER_SEC << " seconds.\n\n";

    // Ready ScoreMatrix
    ScoreMatrix *score_matrix{nullptr};
    if (score_matrix_path != nullptr) {
        double score_matrix_time = clock();
        cout << "ScoreMatrix path: " << score_matrix_path << endl;
        score_matrix = new ScoreMatrix(score_matrix_path);
        cout << "Initialising ScoreMatrix..." << endl;
        cout << "ScoreMatrix initialised in " << (clock()-score_matrix_time)/CLOCKS_PER_SEC  << " seconds.\n\n";
    }

    // Ready Blash
    Blash *blash{nullptr};
    if (hash_algorithm == SimHash::HashAlgorithm::BlosumHash) {
        double blash_time = clock();
        blash = new Blash(score_matrix_path, sliding_window_size, 64, blash_threshold);
        cout << "Initialising Blash hash function..." << endl;
        blash->init_amino_acids();
        cout << "Blash hashing function initialised in " << (clock()-blash_time)/CLOCKS_PER_SEC  << " seconds.\n\n";
    }

    // Ready Alphabet Reduction
    AlphabetReduction *alphabet_reductor{nullptr};
    if(alphabet_reduction_file_path != nullptr) {
        double alphabet_time = clock();
        cout << "Alphabet reduction mapper path: " << alphabet_reduction_file_path << endl;
        alphabet_reductor = new AlphabetReduction(alphabet_reduction_file_path);
        cout << "Initialising alphabet reduction..." << endl;
        alphabet_reductor->construct_mapper();
        cout << "Alphabet reduction mapper initialised in " << (clock()-alphabet_time)/CLOCKS_PER_SEC  << " seconds.\n\n";
    }

    // Init simhash algoritam
    SimHash sim_hash(hash_algorithm, sliding_window_size, mutation_threshold, score_matrix, blash, alphabet_reductor);

    // Comput the simhash
    start = omp_get_wtime();
    #pragma omp parallel num_threads(num_threads)
    {
        size_t cnt = 0;
        int thread_id = omp_get_thread_num();
        int number_of_threads = omp_get_num_threads();

        if(thread_id == 0) {
            cout << "Using " << number_of_threads << " threads to compute ";
            cout << sequence_id_map.size() << " simhashs." << endl;
        }

        for(auto element = sequence_id_map.begin(); element !=sequence_id_map.end(); ++element, cnt++) {
            if(cnt % number_of_threads != thread_id) continue;

            string sequence_hash = sim_hash.hash((*element).second);
            cout << sequence_hash << endl;

            #pragma omp critical
            if(output_file_path != nullptr) {
                output_file_handle << ">" <<(*element).first << endl << sequence_hash << endl;
            }
        }
    }
    cout << "\nSimHashes created in " << (omp_get_wtime()-start) << " seconds." << endl;

    cout << "\nProgram is finished. (press any key to exit)" << endl;
    std::cin.get();
}