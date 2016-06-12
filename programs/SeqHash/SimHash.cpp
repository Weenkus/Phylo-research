//
// Created by weenkus on 4/14/16.
//

#include "SimHash.h"

const int HASH_LENGTH{64};

std::string SimHash::sim_hash(std::string sequence, size_t sliding_window_length, HashAlgorithm hash_algorithm,
                              int mutation_threshold, std::string score_matrix_path, Blash blash) {

    std::vector<int> sim_hash_bit_array (HASH_LENGTH, 0);

    for(unsigned int i = 0; i < sequence.length() - sliding_window_length; i++) {

        std::string window_string = sequence.substr(i, sliding_window_length);

        std::vector<std::string> sequence_samples;
        sequence_samples.push_back(window_string);

        if(mutation_threshold != 0) {
            ScoreMatrix score_matrix(score_matrix_path);

            std::vector<std::string> mutated_sequences = score_matrix.get_mutation_sequences(
                    window_string, mutation_threshold
            );

            sequence_samples.insert(sequence_samples.end(), mutated_sequences.begin(), mutated_sequences.end());
        }

        for(auto sequence : sequence_samples) {
            uint64 window_string_hash{0};
            switch (hash_algorithm) {
                case HashAlgorithm::Spooky:
                    window_string_hash = SpookyHash::Hash64(
                            sequence.c_str(), sliding_window_length, (unsigned)time(NULL)
                    );
                    break;
                case HashAlgorithm::Boost:
                    boost::hash<std::string> string_hash_boost;
                    window_string_hash = string_hash_boost(sequence);
                    break;
                case HashAlgorithm::Native:
                    std::hash<std::string> string_hash_cpp;
                    window_string_hash = string_hash_cpp(sequence);
                    break;
                case HashAlgorithm::BlosumHash:
                    window_string_hash = blash.hash[sequence];
                    break;
            }

            std::string binary_widow_hash = std::bitset<64>(window_string_hash).to_string();
            int j{0};
            for(auto bit :  binary_widow_hash) {
                if (bit == '1')
                    sim_hash_bit_array[j] += 1;
                else
                    sim_hash_bit_array[j] -= 1;
                ++j;
            }
        }
    }

    std::string sim_hash_output;
    for(int i{0}; i < sim_hash_bit_array.size(); ++i) {
        if(sim_hash_bit_array[i] >= 0)
            sim_hash_output.append("1");
        else
            sim_hash_output.append("0");
    }

    return sim_hash_output;
}


