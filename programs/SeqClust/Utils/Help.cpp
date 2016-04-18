//
// Created by weenkus on 4/15/16.
//

#include "Help.h"

using namespace std;

void Help::print_help() {
    cout << "\nSeqClust v0.1 (Alpha) made by Vinko Kodzoman." << endl;
    cout << "\nSeqClust algorithm uses simhash to cluster simhash representations of genomes." << endl << endl;

    cout << "-in                 -       Input file path in the format of fasta files. Fasta file can have multiple sequences.\n";
    cout << "-out                -       Output file path. All simhash values with sequence ids will be written inside.\n";
    cout << "-ham_distance       -       Distance between two genomes (hashes) that are clustered together.\n";
    cout << "-help               -       Print input arguments and program details.\n";
}