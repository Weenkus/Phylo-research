//
// Created by weenkus on 4/15/16.
//

#include "Help.h"

using namespace std;

void Help::print() {
    cout << "\nSeqHash v0.1 (Alpha) made by Vinko Kodzoman." << endl;
    cout << "SeqHash algorithm uses simhash to compute similarity between genomic sequences." << endl << endl;

    cout << "-in                   -       Input file path in the format of fasta files. Fasta file can have multiple sequences.\n\n";

    cout << "-out                  -       Output file path. All simhash values with sequence ids will be written inside.\n"
            "                              The sequences are written in the same format as fasta files (sequence headers are preserved)\n"
            "                              but protein/nucleotide sequences will be represented with a hash string.\n\n";

    cout << "-num_threads          -       Number of threads the program is going to use (1 is default).\n\n";

    cout << "-score_matrix         -       Path to score matrix in .txt format (BLOSUM, PAN).\n\n";

    cout << "-alphabet_reduction   -       Path to alphabet reduction configuration in .txt format.\n"
            "                              All amino acids that belong in the same group should be in one line without spaces.\n\n";

    cout << "-sliding_window       -       Length of the sliding window in the simhash algorithm (8 is default).\n\n";

    cout << "-hash                 -       Name of the hash function used in the simhash algorithm {Boost, Native, Spooky} (Native is default).\n\n";
    cout << "                               Boost       - 64 bit hash from the boost library\n";
    cout << "                               Native      - 64 bit native cpp hash from std (DEFAULT)\n";
    cout << "                               Spooky      - 32, 64, 128 bit hash by Jenkins (64 bit used)\n\n";
    cout << "                               Blash       - 64 bit hash Vinko Kodzoman (only window length 3 works so far)\n\n";

    cout << "-mutation_threshold   -       The program uses BLOSUM62 mutation matrix to generate additional hashes in the construction\n"
            "                              of simhash. Higher threshold means more mutations, thus creating more hashes\n"
            "                              per k-mer (k-window) of the input sequence. (default 0)\n\n";

    cout << "-blash_threshold      -       Same as mutation_threshold but it is used for generating the blash hash function\n\n";

    cout << "-help                 -       Print input arguments and program details.\n";
}