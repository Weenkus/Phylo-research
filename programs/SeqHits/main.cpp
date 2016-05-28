#include <iostream>
#include <string>
#include <unordered_map>
#include <omp.h>
#include <time.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>

#include "Utils/Help.h"
#include "Utils/FastaParser.h"
#include "Core/Hits.h"

using namespace std;

const int MIN_NUM_OF_ARUGMENTS{3};
const int HASH_LENGTH{64};

void non_valid_input_arguments_tell_user(int argc, char *argv[]);
bool is_valid_input_arguments(int argc);
void start_hits(int argc, char *argv[]);


int main(int argc, char *argv[]) {

    if (is_valid_input_arguments(argc)) {
        non_valid_input_arguments_tell_user(argc, argv);
    } else {
        start_hits(argc, argv);
    }
}

void non_valid_input_arguments_tell_user(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "help") == 0 || strcmp(argv[i], "-help") == 0) {
            Help::print_help();
            exit(1);
        }
    }

    cerr << "Invalid number of arguments." << endl;
    cout << "Type help for more information" << endl;
    exit(0);

    // Parse user arguments
}

bool is_valid_input_arguments(int argc) {
    return argc < MIN_NUM_OF_ARUGMENTS;
}

void start_hits(int argc, char *argv[]) {
    char *input_file_path{nullptr}, *output_file_path{nullptr}, *db_file_path{nullptr};
    int num_threads {1}, from_distance{0}, to_distance{0}, chain_number{0}, log_chain{0}, max_sequences{10};

    std::cout << argv[0] << " ";
    for (int i = 1; i < argc; i++) {
        if (i + 1 != argc) {
            if (strcmp(argv[i], "-num_threads") == 0) {
                num_threads = atoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-in") == 0) {
                input_file_path = argv[i + 1];
            } else if (strcmp(argv[i], "-db") == 0) {
                db_file_path = argv[i + 1];
            } else if (strcmp(argv[i], "-out") == 0) {
                output_file_path = argv[i + 1];
            } else if (strcmp(argv[i], "-chain_hits") == 0) {
                from_distance = atoi(argv[i + 1]);
                to_distance = atoi(argv[i + 2]);
                chain_number = atoi(argv[i + 3]);
                max_sequences = atoi(argv[i + 4]);
            } else if (strcmp(argv[i], "-log_chain") == 0) {
                log_chain = atoi(argv[i + 1]);
            } else {
                //cerr << "Invalid arguments, please try again.\n";
                //exit(0);
            }
        }
        cout << argv[i] << " ";
    }

    // Print program attributes
    cout << endl << endl;
    if(input_file_path != nullptr) cout << "Input file: " << input_file_path << endl;
    if(db_file_path != nullptr) cout << "Databse file: " << db_file_path << endl;
    if(output_file_path != nullptr ) cout << "Output file: " << output_file_path << endl;
    cout << "Number of threads: " << num_threads << endl;

    if(chain_number > 0) {
        cout << "From distance: " << from_distance << endl;
        cout << "To distance: " << to_distance << endl;
        cout << "Chain number: " << chain_number << endl;
        cout << "Max sequences: " << max_sequences << endl;
    }


    // Parse input file
    double start = clock();
    unordered_map<string, string> db_sequences = FastaParser::parse_fasta_file(db_file_path);
    unordered_map<string, string> target_sequences = FastaParser::parse_fasta_file(input_file_path);
    cout << "\nParsing database and input files done in " << (clock()-start) / CLOCKS_PER_SEC << " seconds." << endl;

    Hits seqHits(db_sequences, target_sequences, num_threads, from_distance,
                 to_distance, chain_number, log_chain, max_sequences);

    seqHits.run();
    seqHits.write_results_to_file(output_file_path);

    cout << "\nProgram is finished. (press any key to exit)" << endl;
    std::cin.get();
    exit(0);
}