//
// Created by weenkus on 9/25/16.
//

#include "AlphabetReduction.h"

AlphabetReduction::AlphabetReduction(const std::string alphabet_configuration_path):
        _path(alphabet_configuration_path) { }

void AlphabetReduction::construct_mapper() {
    std::ifstream fileHandle(_path);

    std::string line;
    while(std::getline(fileHandle, line)) {
        for(const auto& aminoAcid : line)
            _mapper[aminoAcid] = line[0];
    }
}
