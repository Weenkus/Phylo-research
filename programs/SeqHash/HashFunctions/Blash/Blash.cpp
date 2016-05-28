//
// Created by weenkus on 5/25/16.
//

#include "Blash.h"

Blash::Blash() {
    this->_window_size = 3;
    this->_hash_length = 64;
    this->_mutation_threshold = 12;
}

Blash::Blash(string score_matrix_file_path, size_t window_size, size_t hash_length, int mutation_threshold) {
    this->_score_matrix_file_path = score_matrix_file_path;
    this->_window_size = window_size;
    this->_hash_length = hash_length;
    this->_mutation_threshold = mutation_threshold;
}

void Blash::init_amino_acids() {
    vector<string> amino_acid_permutations = _get_amino_acid_permutations_length_3();
    set<string> amino_acids_already_in_hash;
    ScoreMatrix score_matrix(_score_matrix_file_path);

    std::hash<std::string> string_hash_native_cpp;

    for(auto amino_sequence : amino_acid_permutations) {
        if (contains(amino_acids_already_in_hash, amino_sequence))
            continue;
        amino_acids_already_in_hash.insert(amino_sequence);

        uint64_t amino_hash = string_hash_native_cpp(amino_sequence);
        this->hash[amino_sequence] = amino_hash;

        vector<string> mutated_sequences = score_matrix.get_mutation_sequences(amino_sequence, _mutation_threshold);
        for(auto mutated_amino_seq : mutated_sequences) {
            if (contains(amino_acids_already_in_hash, mutated_amino_seq))
                continue;
            amino_acids_already_in_hash.insert(mutated_amino_seq);

            this->hash[mutated_amino_seq] = amino_hash;
        }
    }

}

vector<string> Blash::_get_amino_acid_permutations_length_3() {
    vector<string> amino_acid_permutations;

    for(auto amino_1 : _amino_acids) {
        for(auto amino_2 : _amino_acids) {
            for(auto amino_3 : _amino_acids) {
                stringstream str_stream;
                str_stream << amino_1 << amino_2 << amino_3;
                amino_acid_permutations.push_back(str_stream.str());
            }
        }
    }
    return amino_acid_permutations;
}

inline const bool Blash::contains(const set<string> container, string element) {
    return container.find(element) != container.end();
}

void Blash::print() {
    for(const auto element : this->hash)
        cout << element.first << " " << element.second << endl;
}


