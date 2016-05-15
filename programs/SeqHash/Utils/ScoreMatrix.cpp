//
// Created by weenkus on 15.05.16..
//

#include "ScoreMatrix.h"

ScoreMatrix::ScoreMatrix(std::string file_path) {
    this->_score_matrix = read_matrix(file_path);
}


int ScoreMatrix::get_value(int x, int y) {
    return this->_score_matrix[x][y];
}


std::vector<std::vector<int>> ScoreMatrix::read_matrix(std::string file_path){
    std::ifstream score_matrix_file(file_path);




    score_matrix_file.close();
}

