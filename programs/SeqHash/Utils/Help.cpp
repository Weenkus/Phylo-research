//
// Created by weenkus on 4/15/16.
//

#include "Help.h"

using namespace std;

void Help::print_help() {
    cout << "\nSeqHash v0.1 (Alpha) made by Vinko Kodzoman." << endl;
    cout << "SeqHash algorithm uses simhash to compute similarity between genomes." << endl << endl;

    cout << "-in                 -       Input file path in the format of fasta files. Fasta file can have multiple sequences.\n";
    cout << "-out                -       Output file path. All simhash values with sequence ids will be written inside.\n";
    cout << "-num_threads        -       Number of threads the program is going to use (1 is default).\n";
    cout << "-sliding_window     -       Length of the sliding window in the simhash algorithm (8 is default).\n";
    cout << "-hash               -       Name of the hash function used in the simhash algorithm {Boost, Native, Spooky} (Native is default).\n";
    cout << "\n                               Boost       - 64 bit hash from the boost library\n";
    cout << "                               Native      - 64 bit native cpp hash from std\n";
    cout << "                               Spooky      - 32, 64, 128 bit hash by Jenkins (64 bit used)\n\n";
    cout << "-help                -      Print input arguments and program details.\n";
}