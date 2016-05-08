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

using namespace std;

const int MIN_NUM_OF_ARUGMENTS{3};
const int HASH_LENGTH{64};

int hamming_distance(std::string string1, std::string string2) {
    int distance = 0;
    for(int i = 0; i < string1.length(); i++)
        distance += (string1[i] != string2[i]);

    return distance;
}

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
        char *input_file_path, *output_file_path, *db_file_path;
        int num_threads {1};

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
        if(db_file_path != NULL) cout << "Databse file: " << db_file_path << endl;
        if(output_file_path != NULL ) cout << "Output file: " << output_file_path << endl;
        cout << "Number of threads: " << num_threads << endl;
        ofstream output_file_handle(output_file_path);

        // Parse input file
        double start = clock();
        unordered_map<string, string> db_map = FastaParser::parse_fasta_file(db_file_path);
        unordered_map<string, string> target_genome_map = FastaParser::parse_fasta_file(input_file_path);
        cout << "\nParsing database and input files done in " << (clock()-start) / CLOCKS_PER_SEC << " seconds." << endl;

        // Compute the hits
        #pragma omp parallel num_threads(num_threads)
        start = omp_get_wtime();
        {
            std::vector<std::pair<int, std::string>> hits_results;
            size_t cnt = 0;
            int thread_id = omp_get_thread_num();
            int number_of_threads = omp_get_num_threads();

            if (thread_id == 0)
                cout << "Using " << number_of_threads << " threads to compute similarity against db of size: " <<
                db_map.size() << endl;

            //for(auto target = target_genome_map.begin(); target !=target_genome_map.end(); ++target) {
            auto target = target_genome_map.begin();
            for (auto element = db_map.begin(); element != db_map.end(); ++element, cnt++) {
                if (cnt % number_of_threads != thread_id) continue;

                cout << (*target).first << (*element).first;

                int ham_distance = hamming_distance((*target).second, (*element).second);
                std::string value = (*target).first + " " + (*element).first + " " + to_string(ham_distance);

                hits_results.push_back(std::make_pair(ham_distance, value));

                cout << (*element).first << endl;
            }

            #pragma omp single
            {
                //sort by key using std::stable_sort
                std::stable_sort(hits_results.begin(), hits_results.end());

                for(auto hit = hits_results.begin(); hit != hits_results.end(); ++hit)
                    output_file_handle << (*hit).second << endl;


                cout << "Hits created in " << (omp_get_wtime()-start) << " seconds." << endl;
            }
        }






        cout << "\nProgram is finished. (press any key to exit)" << endl;
        std::cin.get();
        return 0;
    }

}