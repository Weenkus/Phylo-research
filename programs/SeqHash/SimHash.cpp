//
// Created by weenkus on 4/14/16.
//

#include "SimHash.h"

const int HASH_LENGTH{64};

SimHash::SimHash(HashAlgorithm hash_algorithm, size_t sliding_window_length, int mutation_threshold,
                 ScoreMatrix *score_matrix, Blash *blash, AlphabetReduction *alphabet_reductor) :

    m_hash_algorithm(hash_algorithm),
    m_sliding_window_length(sliding_window_length),
    m_mutation_threshold(mutation_threshold),
    m_score_matrix(score_matrix),
    m_blash(blash),
    m_alphabet_reductor(alphabet_reductor)
{}


std::string SimHash::hash(std::string sequence) {

    std::vector<int> sim_hash_bit_array (HASH_LENGTH, 0);
    if(m_alphabet_reductor != nullptr) {
        sequence = reduce_alphabet(sequence);
    }

    for(unsigned int i = 0; i < sequence.length() - m_sliding_window_length; i++) {

        std::string window_string = sequence.substr(i, m_sliding_window_length);
        std::vector<std::string> sequence_samples;
        sequence_samples.push_back(window_string);

        if(m_mutation_threshold != 0) {
            auto mutated_sequences{m_score_matrix->get_mutation_sequences(window_string, m_mutation_threshold)};
            sequence_samples.insert(sequence_samples.end(), mutated_sequences.begin(), mutated_sequences.end());
        }

        for(auto sequence : sequence_samples) {
            uint64 window_string_hash{hash_sequence(sequence)};
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

    return to_string(sim_hash_bit_array);
}

SimHash::~SimHash() {
    if (m_blash != nullptr) delete m_blash;
    if (m_alphabet_reductor != nullptr) delete m_alphabet_reductor;
    if (m_score_matrix != nullptr) delete m_score_matrix;
}

std::string SimHash::reduce_alphabet(std::string& sequence) {
    for(int i{0}; i < sequence.size(); ++i) {
        sequence[i] = m_alphabet_reductor->map(sequence[i]);
    }
    return sequence;
}

std::string SimHash::to_string(const vector<int> &hash) {
    std::string sim_hash_output;
    sim_hash_output.reserve(hash.size());
    for(int i{0}; i < hash.size(); ++i) {
        if(hash[i] >= 0)
            sim_hash_output.append("1");
        else
            sim_hash_output.append("0");
    }
    return sim_hash_output;
}

uint64 SimHash::hash_sequence(const std::string &sequence) {
    switch (m_hash_algorithm) {
        case HashAlgorithm::Spooky:
            return  SpookyHash::Hash64(sequence.c_str(), m_sliding_window_length, (unsigned)time(NULL));
        case HashAlgorithm::Boost:
            boost::hash<std::string> string_hash_boost;
            return string_hash_boost(sequence);
        case HashAlgorithm::Native:
            std::hash<std::string> string_hash_cpp;
            return string_hash_cpp(sequence);
        case HashAlgorithm::BlosumHash:
            return m_blash->hash[sequence];
    }
}
