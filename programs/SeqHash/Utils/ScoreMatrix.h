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


class ScoreMatrix {

public:
    ScoreMatrix(std::string file_path);

    int get_value(int x, int y);


private:
    std::vector<std::vector<int>> _score_matrix;
    std::map<char, int> _amino_acid_index {{'A', 0}, {'R', 1}, {'N', 2}, {'D', 3}};

    std::vector<std::vector<int>> read_matrix(std::string file_path);

};


#endif //SEQHASH_SCOREMATRIX_H
