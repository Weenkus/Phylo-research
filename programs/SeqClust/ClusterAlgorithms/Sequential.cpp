//
// Created by weenkus on 4/18/16.
//

#include "Sequential.h"

int hamming_distance(std::string string1, std::string string2) {
    int distance = 0;
    for(int i = 0; i < string1.length(); i++)
        distance += (string1[i] != string2[i]);

    return distance;
}

void Sequential::cluster(std::unordered_map<std::string, std::string> genome_hash_dictionary,
                         std::string output_file,
                         int distance) {

    std::vector<std::vector<std::string>> clustered_genomes;
    std::vector<std::string> genomes, used_genomes;

    for(auto &pair : genome_hash_dictionary) {
        genomes.push_back(pair.second);
    }

    int cluster_section = 0;
    for(auto genome1 : genomes) {
        if((std::find(used_genomes.begin(), used_genomes.end(), genome1) != used_genomes.end()))
            continue;

        std::vector<std::string> tempVec;
        tempVec.push_back(genome1);
        clustered_genomes.push_back(tempVec);
        used_genomes.push_back(genome1);

        for(auto genome2 : genomes) {
            if(hamming_distance(genome1, genome2) <= distance
                    && !(std::find(used_genomes.begin(), used_genomes.end(), genome2) != used_genomes.end())) {
                clustered_genomes[cluster_section].push_back(genome2);
                used_genomes.push_back(genome2);
            }
        }
        cluster_section++;
    }

    std::ofstream output_handle(output_file);
    for(auto &cluster : clustered_genomes) {
        for(auto &genome : cluster) {


            for(auto &pair : genome_hash_dictionary) {
                if(genome == pair.second) {
                    output_handle << pair.first << std::endl;
                    output_handle << genome << std::endl;
                    break;
                }
            }
        }
        output_handle << "****************************************************************" << std::endl;
    }

    output_handle.close();
}

