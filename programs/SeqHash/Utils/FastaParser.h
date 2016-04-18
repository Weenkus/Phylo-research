//
// Created by weenkus on 4/14/16.
//

#ifndef SHC_FASTAPARSER_H
#define SHC_FASTAPARSER_H

#include <string>
#include <unordered_map>

class FastaParser {

public:

    static std::unordered_map<std::string, std::string> parse_fasta_file(std::string fasta_file_path);
    static std::string initialise_fasta_file_path(int argc, char **argv);

};


#endif //SHC_FASTAPARSER_H
