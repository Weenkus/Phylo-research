//
// Created by weenkus on 4/14/16.
//

#ifndef SHC_SIMHASH_H
#define SHC_SIMHASH_H

#include "HashFunctions/SpookyV2/SpookyV2.h"

#include <vector>
#include <string>
#include <iostream>

#include <boost/functional/hash.hpp>


class SimHash {

public:

    enum class HashAlgorithm { Boost, Spooky, Native };

    static std::string sim_hash(std::string sequence, size_t sliding_window_length, HashAlgorithm hash_algorithm);

};



#endif //SHC_SIMHASH_H
