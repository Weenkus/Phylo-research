//
// Created by weenkus on 08.05.16..
//

#include "Help.h"

void Help::print_help() {
    cout << "\nSeqHits v0.1 (Alpha) made by Vinko Kodzoman." << endl;
    cout << "SeqHits algorithm uses hemming distance to compute similarity between hash"
                    " representations of their genomes." << endl << endl << endl;

    cout << "-in                        -       Input file path that was made by using SeqHash. Consists a genome you\n"
            "                                   want to match against the db.\n\n";

    cout << "-db                        -       Input file path that was made by using SeqHash. Consists of genomes and\n"
            "                                   their hashes.\n\n";

    cout << "-out                       -       Output file path. Sorted hashes by similarity.\n\n";
    cout << "-num_threads               -       Number of threads the program is going to use (1 is default).\n\n";
    cout << "-help                      -       Print input arguments and program details.\n\n";

    cout << "-log_chain                 -       Write results leading to the final results in a file while using chaining.\n"
            "                                   The default value is \"0\" - don't write. Pass 1 to write the middle results (in a file).\n\n";


    cout << "-chain_hits                -       Uses the results from the algorithm as a query multiple times to obtain\n"
            "                                   sequences with more mutations (evolutionary distant sequences).\n\n\n";

    cout << "   FORMAT:      -chain_hits from_distance to_distance chain_number max_sequences           \n\n\n";

    cout << "          from_distance, to_distance     -    The interval that will determine which sequences are taken\n"
            "                                              from the resulting sequences and queried again.\n\n"
            "          chain_number                   -    The number of times the algorithm repeats the process of taking\n"
            "                                              the result and using it as a query.\n\n";

    cout << "          max_sequences                  -    Maximum number of sequences going to the second round (default 10).\n\n\n";

    cout << "   EXAMPLE:     -chain_hits 1 4 8       -    Take all the sequences with distance 1 to 4 (including) that\n"
            "                                              were generated as a result and re query them 8 times, taking\n"
            "                                              a new query (1,4) distance subset every time a result is generated.\n";
}
