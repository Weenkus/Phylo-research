//
// Created by weenkus on 15.05.16..
//

#ifndef SEQHASH_SCOREMATRIX_H
#define SEQHASH_SCOREMATRIX_H


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>


class ScoreMatrix {

public:
    ScoreMatrix(std::string file_path);

    int get_value(char original_amino_acid, char mutated_amino_acid);
    const std::vector<char> get_amino_acids() const { return m_amino_acids; }
    inline int get_mutation_score(std::string original_sequence, std::string mutated_sequence);

    std::vector<std::string> get_mutation_sequences(std::string sequence, int mutation_threshold);

    void print();


private:
    std::vector<std::vector<int>> m_score_matrix;
    std::map<char, int> m_amino_acid_index {
            {'A', 0}, {'R', 1}, {'N', 2}, {'D', 3}, {'C', 4}, {'Q', 5}, {'E', 6}, {'G', 7}, {'H', 8}, {'I', 9},
            {'L', 10}, {'K', 11}, {'M', 12}, {'F', 13}, {'P', 14}, {'S', 15}, {'T', 16}, {'W', 17}, {'Y', 18},
            {'V', 19}, {'B', 20}, {'Z', 21}, {'X', 22}, {'*', 23}
    };
    std::vector<char> m_amino_acids {
            'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L',
            'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V', 'B', 'Z', 'X'
    };

    std::vector<std::vector<int>> read_matrix(std::string file_path);

};


#endif //SEQHASH_SCOREMATRIX_H
