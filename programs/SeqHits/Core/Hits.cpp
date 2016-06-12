//
// Created by weenkus on 22.05.16..
//

#include "Hits.h"

bool is_not_valid_thread_id(size_t thread_count, int number_of_threads, int thread_id);

Hits::Hits(std::unordered_map<std::string, std::string> db_seq_hashes,
           std::unordered_map<std::string, std::string> target_seq_hash,
           int num_threads, int from_distance, int to_distance, int chain_number, bool log_chain, int max_sequences) {

    this->_db_sequence_hashes = db_seq_hashes;
    this->_target_sequence_hashes = target_seq_hash;

    this->_target_sequence_id = (*_target_sequence_hashes.begin()).first;
    this->_hash_results.insert((*_target_sequence_hashes.begin()).second);

    this->_log_chain_trace = log_chain;

    this->_num_threads = num_threads;
    this->_from_distance = from_distance;
    this->_to_distance = to_distance;
    this->_chain_number = chain_number;
    this->_remaining_iterations = chain_number;
    this->_max_sequences = max_sequences;
}

void Hits::run() {
    if (_chain_number == 0) {
        std::string target_sequence = (*_target_sequence_hashes.begin()).second;
        compute_hits(target_sequence);
    } else {
        for(int i{0}; i < _chain_number; ++i) {

            std::set<std::string> _buffered_hash_results(_hash_results);
            _hash_results.clear();

            std::cout << "Iteration remaining: " << _remaining_iterations << std::endl;

            for(auto target_sequence : _buffered_hash_results) {
                std::cout << "Target sequence: " << target_sequence << std::endl;
                compute_hits_chain(target_sequence);
            }

            --_remaining_iterations;
        }
    }
}

void Hits::compute_hits_chain(std::string target_sequence_hash) {
    {
        double start = omp_get_wtime();

        size_t thread_count = 0;
        int thread_id = omp_get_thread_num();
        int number_of_threads = omp_get_num_threads();

        /*#pragma omp single
        {
            std::cout << "Using " << number_of_threads << " threads to compute similarity against db of size: ";
            std::cout << _db_sequence_hashes.size() << std::endl;
        }*/

        std::set<std::pair<int, std::string>> round_results;

        for (auto element = _db_sequence_hashes.begin();
             element != _db_sequence_hashes.end(); ++element, thread_count++) {

            int ham_distance = hamming_distance(target_sequence_hash, (*element).second);

            if (is_last_hits_round()) {
                std::string target_db_comparison_string = construct_compared_sequence_string(
                        _target_sequence_id, (*element).first, ham_distance);

                _hits_final_results.push_back(std::make_pair(ham_distance, target_db_comparison_string));
            } else {
                round_results.insert(std::make_pair(ham_distance, (*element).second));
            };

        }


        if (is_last_hits_round()) {
            std::cout << "Hits created in " << (omp_get_wtime()-start) << " seconds." << std::endl;
        } else {

            int number_of_next_round_sequences{0};
            for(auto result : round_results) {

                if (is_not_valid_thread_id(thread_count, number_of_threads, thread_id))
                    continue;

                if (result.first > _from_distance && result.first < _to_distance && number_of_next_round_sequences < _max_sequences) {

                    //std::cout << result.second << std::endl;

                    _hash_results.insert(result.second);
                    ++number_of_next_round_sequences;
                }
            }
        }
    }
}

void Hits::compute_hits(std::string target_sequence_hash) {
    double start = omp_get_wtime();

    //#pragma omp parallel num_threads(_num_threads)
    {
        size_t thread_count = 0;
        int thread_id = omp_get_thread_num();
        int number_of_threads = omp_get_num_threads();

        //#pragma omp single
        {
            std::cout << "Starting hits algorithm without chaining.\n";
            std::cout << "Using " << number_of_threads << " threads to compute similarity against db of size: ";
            std::cout << _db_sequence_hashes.size() << std::endl;
        }


        for (auto element = _db_sequence_hashes.begin();
             element != _db_sequence_hashes.end(); ++element, thread_count++) {

            //if(thread_count % number_of_threads != thread_id)
            //    continue;

            std::string db_seq = (*element).second;
            int ham_distance = hamming_distance(target_sequence_hash, db_seq);

            std::string db_seq_id = (*element).first;
            std::string target_db_comparison_string = construct_compared_sequence_string(
                    _target_sequence_id, db_seq_id, ham_distance
            );

            _hits_final_results.push_back(std::make_pair(ham_distance, target_db_comparison_string));
            std::cout << db_seq_id << " " << db_seq << std::endl;
        }
    }

    std::cout << "Hits created in " << (omp_get_wtime()-start) << " seconds." << std::endl;
}

int Hits::hamming_distance(std::string sequence1, std::string sequence2) {
    int distance = 0;

    for(int i = 0; i < sequence1.length(); i++)
        distance += (sequence1[i] != sequence2[i]);

    return distance;
}

void Hits::write_results_to_file(std::string file_path) {
    {
        std::ofstream output_file_handle(file_path);

        //sort by key using std::stable_sort
        std::stable_sort(_hits_final_results.begin(), _hits_final_results.end());

        for(auto hit = _hits_final_results.begin(); hit != _hits_final_results.end(); ++hit)
            output_file_handle << (*hit).second << std::endl;

    }
}

std::string Hits::construct_compared_sequence_string(std::string sequence_from_db, std::string target_sequence, int ham_distance) {
    return sequence_from_db + " " + target_sequence + " " +  std::to_string(ham_distance);
}


bool Hits::is_not_valid_thread_id(size_t thread_count, int number_of_threads, int thread_id) {
    return thread_count % number_of_threads != thread_id;
}

bool Hits::is_last_hits_round() {
    return _remaining_iterations == 1;
}

