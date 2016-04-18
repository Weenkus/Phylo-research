//
// Created by weenkus on 4/18/16.
//

#ifndef SEQCLUST_SEQUENTIAL_H
#define SEQCLUST_SEQUENTIAL_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>


class Sequential {

public:

    static void cluster(std::unordered_map<std::string, std::string> genome_hash_dictionary,
                        std::string output_file,
                        int distance);

};


#endif //SEQCLUST_SEQUENTIAL_H
