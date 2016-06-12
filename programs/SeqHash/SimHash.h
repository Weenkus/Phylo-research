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
#include "HashFunctions/SpookyV2/SpookyV2.h"


class SimHash {

public:

    enum HashAlgorithm { Boost, Spooky, Native, BlosumHash };

    static std::string sim_hash(std::string sequence, size_t sliding_window_length, HashAlgorithm hash_algorithm,
                                int mutation_threshold, std::string score_matrix_path, Blash blash);

};



#endif //SHC_SIMHASH_H
