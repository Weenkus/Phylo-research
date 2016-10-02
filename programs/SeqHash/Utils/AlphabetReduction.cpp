//
// Created by weenkus on 9/25/16.
//

#include "AlphabetReduction.h"

AlphabetReduction::AlphabetReduction(const std::string alphabet_configuration_path):
        m_path(alphabet_configuration_path) { }

void AlphabetReduction::construct_mapper() {
    std::ifstream fileHandle(m_path);

    std::string line;
    while(std::getline(fileHandle, line)) {
        for(const auto& aminoAcid : line)
            m_mapper[aminoAcid] = line[0];
    }
}

void AlphabetReduction::print() {
    for(auto it = m_mapper.begin(); it != m_mapper.end(); ++it) {
        auto element = (*it);
        std::cout << element.first << " " << element.second << std::endl;
    }
}


