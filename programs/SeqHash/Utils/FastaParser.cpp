//
// Created by weenkus on 4/14/16.
//

#include "FastaParser.h"

#include <fstream>
#include <iostream>

const std::string FASTA_FILE_PATH {"../../../../datasets/eColiStrains.fasta"};

std::unordered_map<std::string, std::string> FastaParser::parse_fasta_file(std::string fasta_file_path) {
    std::ifstream fasta_file_handle(fasta_file_path);

    if(!fasta_file_handle.good()) {
        std::cerr << "ERROR opening " << fasta_file_path << std::endl;
        exit(0);
    }

    std::string line, id, dna_sequence;
    std::unordered_map<std::string, std::string> id_dna_map;
    while (std::getline(fasta_file_handle, line)) {

        if(line.empty())
            continue;

        if (line[0] == '>') {
            if(!id.empty()) {
                std::cout << id << std::endl;
                id_dna_map[id] = dna_sequence;
            }

            id = line.substr(1);
            dna_sequence.clear();
        } else {
            dna_sequence += line;
        }
    }

    fasta_file_handle.close();
    return id_dna_map;
}

std::string FastaParser::initialise_fasta_file_path(int argc, char **argv) {
    return argc >= 2 ? argv[1] : FASTA_FILE_PATH;
}
