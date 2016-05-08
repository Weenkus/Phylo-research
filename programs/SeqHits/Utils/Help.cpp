//
// Created by weenkus on 08.05.16..
//

#include "Help.h"

void Help::print_help() {
    cout << "\nSeqHits v0.1 (Alpha) made by Vinko Kodzoman." << endl;
    cout << "SeqHits algorithm uses hemming distance to compute similarity between hash"
                    " representations of their genomes." << endl << endl;

    cout << "-in                 -       Input file path that was made by using SeqHash. Consists a genome you want to match against the db.\n";
    cout << "-db                 -       Input file path that was made by using SeqHash. Consists of genomes and their hashes.\n";
    cout << "-out                -       Output file path. Sorted hashes by similarity.\n";
    cout << "-num_threads        -       Number of threads the program is going to use (1 is default).\n";
    cout << "-help                -      Print input arguments and program details.\n";
}
