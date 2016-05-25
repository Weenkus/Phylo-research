//
// Created by weenkus on 5/25/16.
//

#include "Blash.h"

Blash::Blash(string score_matrix_file_path, size_t window_size, size_t hash_length, int mutation_threshold) {
    this->_score_matrix_file_path = score_matrix_file_path;
    this->_window_size = window_size;
    this->_hash_length = hash_length;
    this->_mutation_threshold = mutation_threshold;
}

void Blash::init_amino_acids() {
    vector<string> amino_acid_permutations = _get_amino_acid_permutations(amino_acid_permutations, 0);
    vector<string> amino_acids_already_in_hash;
    ScoreMatrix score_matrix(_score_matrix_file_path);

    for(auto amino_sequence : amino_acid_permutations) {
        vector<string> mutated_sequences = score_matrix.get_mutation_sequences(amino_sequence, _mutation_threshold);


    }

}

vector<string> Blash::_get_amino_acid_permutations(vector<string> amino_acid_permutations, size_t length) {

    if(length == _window_size)
        return amino_acid_permutations;

    if(length == 0){
        for(auto amino : _amino_acids) {
            amino_acid_permutations.push_back(to_string(amino));
            _get_amino_acid_permutations(amino_acid_permutations, 1);
        }

    }

    for(int i{0}; i < amino_acid_permutations.size(); ++i) {
        for(auto amino : _amino_acids) {
            amino_acid_permutations[i] = strcat(amino_acid_permutations[i], to_string(amino));
        }
        _get_amino_acid_permutations(amino_acid_permutations, length + 1);
    }
}
