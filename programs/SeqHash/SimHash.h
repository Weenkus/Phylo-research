//
// Created by weenkus on 4/14/16.
//

#ifndef SHC_SIMHASH_H
#define SHC_SIMHASH_H


#include "Utils/ScoreMatrix.h"

#include <vector>
#include <string>
#include <iostream>

#include <boost/functional/hash.hpp>
#include "HashFunctions/Blash/Blash.h"
#include "Utils/AlphabetReduction.h"
#include "HashFunctions/SpookyV2/SpookyV2.h"


class SimHash {



public:
    enum HashAlgorithm { Boost, Spooky, Native, BlosumHash };

    SimHash(HashAlgorithm hash_algorithm, size_t sliding_window_length, int mutation_threshold,
            ScoreMatrix *m_score_matrix, Blash *m_blash, AlphabetReduction *m_alphabet_reductor);
    ~SimHash();

    std::string hash(std::string sequence);


private:

    HashAlgorithm m_hash_algorithm;
    size_t m_sliding_window_length;
    int m_mutation_threshold;
    ScoreMatrix *m_score_matrix;
    Blash *m_blash;
    AlphabetReduction *m_alphabet_reductor;

    std::string reduce_alphabet(std::string &sequence);
    std::string to_string(const vector<int> &hash);
    uint64 hash_sequence(const std::string &sequence);
};



#endif //SHC_SIMHASH_H
