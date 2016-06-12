//
// Created by weenkus on 5/25/16.
//

#ifndef SEQHASH_BLASH_H
#define SEQHASH_BLASH_H

#include "../../Utils/ScoreMatrix.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>

using namespace std;

class Blash {

public:
    Blash();
    Blash(string score_matrix_file_path, size_t window_size, size_t hash_length, int mutation_threshold);

    void init_amino_acids();
    void print();

    unordered_map<string, uint64_t> hash;

private:
    size_t _window_size;
    size_t _hash_length;
    int _mutation_threshold;
    string _score_matrix_file_path;

    vector<char> _amino_acids {
            'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L',
            'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V', 'B', 'Z', 'X'
    };

    vector<std::string> _get_amino_acid_permutations_length_3();

    inline const bool contains(const set<string> container, string element);
};


#endif //SEQHASH_BLASH_H
