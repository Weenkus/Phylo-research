#include <iostream>
#include <string>
#include <unordered_map>
#include <omp.h>
#include <time.h>
#include <fstream>
#include <string.h>

#include "Utils/Help.h"
#include "Utils/HashParser.h"

#include "ClusterAlgorithms/Sequential.h"

const int MIN_NUM_OF_ARUGMENTS{3};

using namespace std;

int main(int argc, char *argv[]) {
    // Check if the user entered enough arguments
    if (argc < MIN_NUM_OF_ARUGMENTS) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "help") == 0 || strcmp(argv[i], "-help") == 0) {
                Help::print_help();
                return 0;
            }
        }

        cerr << "Invalid number of arguments." << endl;
        cout << "Type help for more information" << endl;
        exit(0);

        // Parse user arguments
    } else {
        char *input_file_path, *output_file_path;
        int distance{1};

        std::cout << argv[0] << " ";
        for (int i = 1; i < argc; i++) {
            if (i + 1 != argc) {
                if (strcmp(argv[i], "-ham_distance") == 0) {
                    distance = atoi(argv[i + 1]);
                } else if (strcmp(argv[i], "-in") == 0) {
                    input_file_path = argv[i + 1];
                } else if (strcmp(argv[i], "-out") == 0) {
                    output_file_path = argv[i + 1];
                }
            }
            cout << argv[i] << " ";
        }
        cout << endl;

        unordered_map<string, string> hash_genomes = HashParser::parse_hash(input_file_path);
        Sequential::cluster(hash_genomes, output_file_path, distance);
    }

    return 0;
}