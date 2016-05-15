//
// Created by weenkus on 15.05.16..
//

#include "ScoreMatrix.h"

ScoreMatrix::ScoreMatrix(std::string file_path) {
    _score_matrix = read_matrix(file_path);
}


int ScoreMatrix::get_value(char original_amino_acid, char mutated_amino_acid) const {
    return _score_matrix[_amino_acid_index[original_amino_acid]][_amino_acid_index[mutated_amino_acid]];
}

void ScoreMatrix::print() {
    std::cout << "ScoreMatrix (BLOSUM62) :" << std::endl;

    for(auto row : _score_matrix) {
        for(auto element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}


int ScoreMatrix::get_mutation_score(std::string original_sequence, std::string mutated_sequence) const {
    int mutation_score{0};
    for(int i{0}; i < original_sequence.length(); ++i) {
        mutation_score += get_value(original_sequence.at(i), mutated_sequence.at(i));
    }

    return mutation_score;
}

std::vector<std::string> ScoreMatrix::get_mutation_sequences(std::string sequence, int mutation_threshold) const {
    std::vector<std::string> mutated_sequences;

    for(int i{0}; i < sequence.length(); ++i) {
        for(auto &amino_acid : _amino_acids) {

            std::string mutated_sequence = sequence;
            mutated_sequence[i] = amino_acid;

            if(get_mutation_score(sequence, mutated_sequence) <= mutation_threshold)
                mutated_sequences.push_back(mutated_sequence);
        }
    }

    return mutated_sequences;
}


std::vector<std::vector<int>> ScoreMatrix::read_matrix(std::string file_path){
    std::ifstream score_matrix_file(file_path);
    if(!score_matrix_file.is_open()) {
        std::cerr << "Unable to open: " << file_path << std::endl;
        exit(0);
    }

    std::vector<std::vector<int>> score_matrix;
    std::string line;

    int i = -1;
    while (std::getline(score_matrix_file, line)) {
        ++i;
        if(i == 0)
            continue;

        std::vector<std::string> mutations_str;
        boost::replace_all(line, "  ", " ");    // Normalize spaces to one space
        boost::split(mutations_str, line, boost::is_any_of(" "));

        std::vector<int> mutations_int;
        int j = -1;
        for(auto &mutation : mutations_str) {
            ++j;
            if(j == 0)
                continue;

            mutations_int.push_back(atoi(mutation.c_str()));
        }

        score_matrix.push_back(mutations_int);
    }

    score_matrix_file.close();
    return score_matrix;
}

