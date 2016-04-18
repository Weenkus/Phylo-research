//
// Created by weenkus on 4/18/16.
//

#ifndef SEQCLUST_HASHPARSER_H
#define SEQCLUST_HASHPARSER_H

#include <unordered_map>
#include <string>
#include <fstream>

class HashParser {

public:

    static std::unordered_map<std::string, std::string> parse_hash(std::string file_path);

};


#endif //SEQCLUST_HASHPARSER_H
