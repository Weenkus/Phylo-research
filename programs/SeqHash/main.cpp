#include <iostream>
#include <string>
#include <unordered_map>
#include <omp.h>
#include <time.h>
#include <fstream>

#include "Utils/FastaParser.h"
#include "SimHash.h"
#include "Utils/Help.h"

using namespace std;

const int MIN_NUM_OF_ARUGMENTS{3};

int main(int argc, char *argv[]) {

    // Check if the user entered enough arguments
    if (argc < MIN_NUM_OF_ARUGMENTS) {
        for (int i = 1; i < argc; i++) {
            if (std::strcmp(argv[i], "help") == 0 || std::strcmp(argv[i], "-help") == 0) {
                Help::print_help();
                return 0;
            }
        }

        cerr << "Invalid number of arguments." << endl;
        cout << "Type help for more information" << endl;
        exit(0);

    // Parse user arguments
    } else {
        char* input_file_path, *hash, *output_file_path;
        int num_threads {1}, sliding_window_size{8};
        SimHash::HashAlgorithm hash_algorithm = SimHash::HashAlgorithm::Native;

        std::cout << argv[0] << " ";
        for (int i = 1; i < argc; i++) {
            if (i + 1 != argc) {
                if (std::strcmp(argv[i], "-num_threads") == 0) {
                    num_threads = atoi(argv[i + 1]);
                } else if (std::strcmp(argv[i], "-in") == 0) {
                    input_file_path = argv[i + 1];
                } else if (std::strcmp(argv[i], "-out") == 0) {
                    output_file_path = argv[i + 1];
                } else if (std::strcmp(argv[i], "-hash") == 0) {
                    hash = argv[i + 1];
                    if (std::strcmp(hash, "Native")) {
                        hash_algorithm = SimHash::HashAlgorithm::Native;
                    } else if (std::strcmp(hash, "Boost")) {
                        hash_algorithm = SimHash::HashAlgorithm::Boost;
                    } else if (std::strcmp(hash, "Spooky")) {
                        hash_algorithm = SimHash::HashAlgorithm::Spooky;
                    } else {
                        cerr << "Hashing algorithm " << hash << " doesn't exists." << endl;
                        exit(0);
                    }
                } else if (std::strcmp(argv[i], "-sliding_window") == 0) {
                    sliding_window_size = atoi(argv[i + 1]);
                } else {
                    //cerr << "Invalid arguments, please try again.\n";
                    //exit(0);
                }
            }
            cout << argv[i] << " ";
        }

        // Print program atributes
        cout << endl << endl;
        if(input_file_path != NULL) cout << "Input file: " << input_file_path << endl;
        if(output_file_path != NULL ) cout << "Output file: " << output_file_path << endl;
        cout << "Number of threads: " << num_threads << endl;
        if(hash != NULL ) cout << "Hash function: " << hash << endl;
        cout << "Sliding window length: " << sliding_window_size << endl << endl;
        ofstream output_file_handle(output_file_path);

        // Parse input file
        double start = clock();
        unordered_map<string, string> sequence_id_map = FastaParser::parse_fasta_file(input_file_path);
        cout << "\nParsing done in " << (clock()-start) / CLOCKS_PER_SEC << " seconds." << endl;

        // Comput the simhash
        start = omp_get_wtime();
        #pragma omp parallel num_threads(num_threads)
        {
            size_t cnt = 0;
            int thread_id = omp_get_thread_num();
            int number_of_threads = omp_get_num_threads();

            if(thread_id == 0)
                cout << "Using " << number_of_threads << " threads to compute " << sequence_id_map.size() << " simhashs." << endl;

            for(auto element = sequence_id_map.begin(); element !=sequence_id_map.end(); ++element, cnt++) {
                if(cnt % number_of_threads != thread_id) continue;

                string sequance_hash = SimHash::sim_hash((*element).second, sliding_window_size, hash_algorithm);
                cout << sequance_hash << endl;

                #pragma omp critical
                if(output_file_path != NULL) {
                    output_file_handle << ">" <<(*element).first << endl << sequance_hash << endl;
                }
            }
        }
        cout << "SimHashes created in " << (omp_get_wtime()-start) << " seconds." << endl;


        cout << "\nProgram is finished. (press any key to exit)" << endl;
        std::cin.get();
        return 0;
    }
}