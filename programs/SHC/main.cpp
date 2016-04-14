#include <iostream>
#include <string>
#include <unordered_map>

#include "Utils/FastaParser.h"
#include "SimHash.h"

using namespace std;


int main(int argc, char *argv[]) {
    string file_path{FastaParser::initialise_fasta_file_path(argc, argv)};
    unordered_map<string, string> sequence_id_map = FastaParser::parse_fasta_file(file_path);

    for(auto pair : sequence_id_map) {
        cout << SimHash::sim_hash(pair.second, 4, SimHash::HashAlgorithm::Native) << endl;
    }

    return 0;
}