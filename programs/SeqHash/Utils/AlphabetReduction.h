//
// Created by weenkus on 9/25/16.
//

#ifndef SEQHASH_ALPHABETREDUCTION_H
#define SEQHASH_ALPHABETREDUCTION_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

class AlphabetReduction {
public:
    AlphabetReduction(const std::string alphabet_configuration_path);

    void construct_mapper();
    void print();

    inline char map(char amino_acid) { return m_mapper[amino_acid]; }

private:
    const std::string m_path;
    std::unordered_map<char, char> m_mapper;
};


#endif //SEQHASH_ALPHABETREDUCTION_HM
