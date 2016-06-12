//
// Created by weenkus on 22.05.16..
//

#ifndef SEQHITS_HITS_H
#define SEQHITS_HITS_H


#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

class Hits {

public:
    Hits(
            std::unordered_map<std::string, std::string> db_seq_hashes,
            std::unordered_map<std::string, std::string> target_seq_hash,
            int num_threads,
            int from_distance,
            int to_distance,
            int chain_number,
            bool log_chain,
            int max_sequences
    );

    void run();
    void write_results_to_file(std::string file_path);


private:
    std::unordered_map<std::string, std::string> _db_sequence_hashes;
    std::unordered_map<std::string, std::string> _target_sequence_hashes;

    std::vector<std::pair<int, std::string>> _hits_final_results;
    std::unordered_map<std::string, int> _results_map;
    std::set<std::string> _hash_results;

    std::string _target_sequence_id;

    bool _log_chain_trace{false};
    int _num_threads{1}, _from_distance{0}, _to_distance{0}, _chain_number{0}, _remaining_iterations{0}, _max_sequences{10};

    void compute_hits_chain(std::string target_sequence_hash);
    void compute_hits(std::string target_sequence_hash);
    int hamming_distance(std::string sequence1, std::string sequence2);
    bool is_not_valid_thread_id(size_t thread_count, int number_of_threads, int thread_id);
    std::string construct_compared_sequence_string(
            std::string sequence_from_db, std::string target_sequence, int ham_distance
    );
    bool is_last_hits_round();
};


#endif //SEQHITS_HITS_H
