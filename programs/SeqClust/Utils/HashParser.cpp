//
// Created by weenkus on 4/18/16.
//

#include <iostream>
#include "HashParser.h"

std::unordered_map<std::string, std::string> HashParser::parse_hash(std::string file_path) {
    std::ifstream input_handle(file_path);

    std::unordered_map<std::string, std::string> hash_genome_dictionary;
    std::string line, genome_id;
    while (std::getline(input_handle, line)) {
        if(line.empty() || line[0] =='\n')
            continue;

        if(line[0] == '0' || line[0] == '1') {
            hash_genome_dictionary[genome_id] = line;
        } else {
            genome_id = line;
        }
    }

    input_handle.close();
    return hash_genome_dictionary;
}
