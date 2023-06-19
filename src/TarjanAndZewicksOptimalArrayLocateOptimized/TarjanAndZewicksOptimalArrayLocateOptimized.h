//
// Created by Abhijith  K A on 30/03/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_H
#define RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_H

#include "Constants.h"
#include "StandardBaseBCounter.h"
#include <vector>
#include <cmath>
#include "TarjansArrayStateFullReadIterator.h"
#include "TarjansArrayStateFullReadReverseIterator.h"
#include "StateFullReadReverseWithDeleteBlockIterator.h"

namespace TarjanAndZewicksOptimalArrayLocateOptimized{

    constexpr TZA_index_t default_r = 4;
    constexpr double default_growth_factor = 2;
    constexpr int default_block_size = 4;

    template<class T, TZA_index_t r = default_r, TZA_index_t initial_block_size = default_block_size>


    class TarjanAndZewicksOptimalArray {
        std::vector<TZA_index_t> block_type_to_count_map_;
        std::vector<std::vector<T*>> index_blocks_list_;
        std::vector<TZA_index_t> powers_of_b_;
        std::vector<TZA_index_t> redundant_base_b_counter_;
        TZA_index_t current_base_block_size_;
        TZA_index_t size_;
        TZA_index_t current_base_block_size_power_r_;
        TZA_index_t current_base_block_size_log_2_;
        TZA_index_t current_base_block_size_log_log_2_;
        TZA_index_t locate_mask_;
        bool is_current_block_size_multiple_of_two_;
        TZA_index_t current_base_block_size_division_four_power_r_;
        T* empty_block = nullptr;
        bool is_empty_block_present = false;
        StandardBaseBCounter standardBaseBCounter_;

        T* Allocate(TZA_index_t block_size){
            return new T[block_size];
        }
        void DeAllocate(T* block_pointer, [[maybe_unused]] TZA_index_t block_size){
            delete[] block_pointer;
        }

        [[nodiscard]] TZA_index_t GetMSB(TZA_index_t number) const{
            int msb = 63 - __builtin_clzll(number);
            return msb;
        }

        void Rebuild(double growth_factor) {
            TZA_index_t new_base_block_size = std::ceil(current_base_block_size_ * growth_factor);
            TZA_index_t new_base_block_size_power_r = std::pow(new_base_block_size, r);
            TZA_index_t elements_left_to_copy = size_;



            TZA_index_t active_old_block_type_id = r - 1;
            TZA_index_t active_old_block_index_in_old_block_type = 0;
            TZA_index_t active_old_element_index_in_active_old_block = 0;
            TZA_index_t active_old_block_id_block_size = powers_of_b_.at(active_old_block_type_id);
            TZA_index_t block_count_in_active_old_block_id = block_type_to_count_map_.at(r - 1);

            if(is_empty_block_present){
                DeAllocate(empty_block, current_base_block_size_);
            }
            is_empty_block_present = false;


            std::vector<TZA_index_t> new_block_type_to_count_map(r, 0);
            std::vector<TZA_index_t> new_powers_of_b;
            new_powers_of_b.resize(r, 0);
            std::vector<TZA_index_t> new_redundant_base_block_representation;
            new_redundant_base_block_representation.resize(r, 0);

            TZA_index_t active_new_power_of_b = 1;
            for(TZA_index_t& power_of_b : new_powers_of_b){
                power_of_b = active_new_power_of_b;
                active_new_power_of_b *= new_base_block_size;
            }



            TZA_index_t active_new_block_type_id = r - 1;
            TZA_index_t block_size_for_active_new_block_id = new_base_block_size_power_r / new_base_block_size;
            TZA_index_t block_count_in_active_new_block_id = 0;



            std::vector<std::vector<T*>> index_list_for_blocks(r);


            while (elements_left_to_copy > 0) {

                if (block_count_in_active_new_block_id > (2 * (new_base_block_size - 1))){
                    new_redundant_base_block_representation.at(active_new_block_type_id) += 1;
                    --active_new_block_type_id;
                    block_size_for_active_new_block_id = new_powers_of_b.at(active_new_block_type_id);
                    if(active_new_block_type_id == 0){
                        block_size_for_active_new_block_id = new_base_block_size;
                    }
                    block_count_in_active_new_block_id = 0;
                }
                else if (block_size_for_active_new_block_id > elements_left_to_copy && active_new_block_type_id > 0) {
                    //new_redundant_base_block_representation.at(active_new_block_type_id) += 1;
                        --active_new_block_type_id;
                        block_size_for_active_new_block_id = new_powers_of_b.at(active_new_block_type_id);
                        if(active_new_block_type_id == 0){
                            block_size_for_active_new_block_id = new_base_block_size;
                        }
                        block_count_in_active_new_block_id = 0;
                }
                else {
                    std::vector<T*> & list_for_storing_blocks_in_current_block_id = index_list_for_blocks.at(active_new_block_type_id);
                    T* active_new_block_start_address = Allocate(block_size_for_active_new_block_id);
                    TZA_index_t active_new_elements_in_new_block_index = 0;
                    while(active_new_elements_in_new_block_index < block_size_for_active_new_block_id && elements_left_to_copy > 0){
                            if (block_count_in_active_old_block_id == 0 ||
                                   active_old_block_index_in_old_block_type >=
                                   block_count_in_active_old_block_id) {
                            --active_old_block_type_id;
                            active_old_block_index_in_old_block_type = 0;
                            active_old_element_index_in_active_old_block = 0;
                            active_old_block_id_block_size =
                                    powers_of_b_.at(active_old_block_type_id);
                            block_count_in_active_old_block_id = block_type_to_count_map_.at(
                                    active_old_block_type_id);
                            if(active_old_block_type_id == 0){
                                active_old_block_id_block_size = current_base_block_size_;
                                block_count_in_active_old_block_id = 2;
                            }
                        } else if (active_old_element_index_in_active_old_block >=
                                   active_old_block_id_block_size) {
                            DeAllocate(index_blocks_list_.at(active_old_block_type_id).at(active_old_block_index_in_old_block_type), active_old_block_id_block_size);
                            ++active_old_block_index_in_old_block_type;
                            active_old_element_index_in_active_old_block = 0;
                        } else {
                            T old_item = std::move(index_blocks_list_.at(active_old_block_type_id).at(
                                    active_old_block_index_in_old_block_type)[active_old_element_index_in_active_old_block]);
                            ++active_old_element_index_in_active_old_block;
                            active_new_block_start_address[active_new_elements_in_new_block_index] = std::move(old_item);
                            ++active_new_elements_in_new_block_index;
                            --elements_left_to_copy;
                        }
                    }
                    if(elements_left_to_copy <= 0 && active_new_block_type_id == 1){
                        //new_block_type_to_count_map.at(0) = active_new_elements_in_new_block_index;
                    }
                    if(elements_left_to_copy == 0){
                        if(active_old_block_index_in_old_block_type < block_count_in_active_old_block_id){
                            DeAllocate(index_blocks_list_.at(active_old_block_type_id).at(
                                    active_old_block_index_in_old_block_type), active_old_block_id_block_size);
                        }
                    }
                    ++block_count_in_active_new_block_id;
                    new_redundant_base_block_representation.at(active_new_block_type_id) += 1;
                    if(active_new_block_type_id > 0) {
                        ++new_block_type_to_count_map.at(active_new_block_type_id);
                    }
                    else if(active_new_block_type_id == 0){
                        if(elements_left_to_copy > 0){
                            new_block_type_to_count_map.at(active_new_block_type_id) = new_base_block_size + elements_left_to_copy;
                        }
                    }
                    list_for_storing_blocks_in_current_block_id.push_back(active_new_block_start_address);
                }
            }

            index_blocks_list_ = std::move(index_list_for_blocks);
            block_type_to_count_map_ = std::move(new_block_type_to_count_map);
            current_base_block_size_ = new_base_block_size;
            current_base_block_size_power_r_ = new_base_block_size_power_r;
            current_base_block_size_division_four_power_r_ = std::pow(new_base_block_size/4, r);
            current_base_block_size_log_2_ = std::ceil(std::log2(new_base_block_size));
            current_base_block_size_log_log_2_ =  std::ceil(std::log2(current_base_block_size_log_2_));
            locate_mask_ = (1 << current_base_block_size_log_2_) - 1;
            TZA_index_t redundant_base_block_counter_for_r = 0;
            TZA_index_t type_index = r - 1;
            for(TZA_index_t & r_i : redundant_base_b_counter_){
                r_i = redundant_base_block_counter_for_r + (new_redundant_base_block_representation.at(type_index) * new_powers_of_b.at(type_index));
                redundant_base_block_counter_for_r += (new_redundant_base_block_representation.at(type_index) * new_powers_of_b.at(type_index));
                --type_index;
            }
            std::reverse(redundant_base_b_counter_.begin(), redundant_base_b_counter_.end());
            powers_of_b_ = std::move(new_powers_of_b);
        }

        void Rebuild3(double growth_factor){
            Rebuild(growth_factor);
            if(block_type_to_count_map_[1] == 0 && block_type_to_count_map_[0] == 0){
                SplitBlocks();
            }
            else if(r == 2 && block_type_to_count_map_[0] == 0){
                SplitBlocks();
            }
        }

        void Rebuild2(double growth_factor){

            TZA_index_t new_base_block_size = std::ceil(current_base_block_size_ * growth_factor);
            TZA_index_t new_base_block_size_power_r = std::pow(new_base_block_size, r);
            TZA_index_t elements_left_to_copy = size_;

            if(is_empty_block_present){
                DeAllocate(empty_block, current_base_block_size_);
            }
            is_empty_block_present = false;

            std::vector<TZA_index_t> new_block_type_to_count_map(r, 0);
            std::vector<TZA_index_t> new_powers_of_b;
            new_powers_of_b.resize(r, 0);
            std::vector<TZA_index_t> new_redundant_base_block_representation;
            new_redundant_base_block_representation.resize(r, 0);
            std::vector<std::vector<T*>> new_index_list_for_blocks(r);

            StateFullReadReverseWithDeleteBlockIterator<T,r> stateFullReadReverseWithDeleteBlockIterator{block_type_to_count_map_, index_blocks_list_, powers_of_b_, size_};

            TZA_index_t current_block_type = 0;
            TZA_index_t current_block_size = new_base_block_size;
            TZA_index_t items_left_to_iterate = size_;

            TZA_index_t blocks_remaining = items_left_to_iterate;

            TZA_index_t blocks_in_current_level = blocks_remaining % new_base_block_size;
            TZA_index_t current_block_index = 0;



            TZA_index_t current_element_position = blocks_in_current_level - 1;
            if(blocks_in_current_level > 0) {
                T *new_level_zero_block_start_address = Allocate(new_base_block_size);
                new_index_list_for_blocks[0].push_back(new_level_zero_block_start_address);
                new_block_type_to_count_map[0] = blocks_in_current_level;
                while (blocks_in_current_level > 0) {
                    new_level_zero_block_start_address[current_element_position] = stateFullReadReverseWithDeleteBlockIterator.GetNextItem();
                    --current_element_position;
                    --items_left_to_iterate;
                    --blocks_in_current_level;
                }
            }
            new_redundant_base_block_representation[0] = blocks_in_current_level;

//            ++current_block_type;
//            blocks_remaining = blocks_remaining / new_base_block_size;
//            blocks_in_current_level = blocks_remaining % current_block_size;
//            new_redundant_base_block_representation[current_block_type] = blocks_in_current_level;
//            new_block_type_to_count_map[current_block_type] = blocks_in_current_level;
//            current_element_position = current_block_size - 1;
            current_block_size = 1;




            while(items_left_to_iterate > 0){
                T* active_block_start_address;
                if(blocks_in_current_level > 0) {
                    if(current_element_position == 0){
                        --current_block_index;
                        new_index_list_for_blocks[current_block_type][current_block_index] = Allocate(current_block_size);
                        current_element_position = current_block_size - 1;
                        --blocks_in_current_level;
                    }
                    active_block_start_address = new_index_list_for_blocks[current_block_type][current_block_index];
                }
                else{
                    while(blocks_in_current_level == 0) {
                        ++current_block_type;
                        current_block_size *= new_base_block_size;
                        blocks_remaining = blocks_remaining/ new_base_block_size;
                        blocks_in_current_level = blocks_remaining % new_base_block_size;
                        new_redundant_base_block_representation[current_block_type] = blocks_in_current_level;
                        new_block_type_to_count_map[current_block_type] = blocks_in_current_level;
                    }
                    current_element_position = current_block_size - 1;
                    current_block_index = blocks_in_current_level - 1;
                    new_index_list_for_blocks[current_block_type].resize(blocks_in_current_level, nullptr);
                    new_index_list_for_blocks[current_block_type][current_block_index] = Allocate(current_block_size);
                    active_block_start_address = new_index_list_for_blocks[current_block_type][current_block_index];
                }

                while(true){
                    active_block_start_address[current_element_position] = stateFullReadReverseWithDeleteBlockIterator.GetNextItem();
                    --items_left_to_iterate;
                    if(current_element_position == 0){
                        break;
                    }
                    --current_element_position;
                }

            }


            current_base_block_size_ = new_base_block_size;
            current_base_block_size_log_2_ += growth_factor;
            index_blocks_list_ = std::move(new_index_list_for_blocks);
            block_type_to_count_map_ = std::move(new_block_type_to_count_map);

            current_base_block_size_ = new_base_block_size;
            current_base_block_size_power_r_ = new_base_block_size_power_r;
            current_base_block_size_division_four_power_r_ = std::pow(new_base_block_size/4, r);
            current_base_block_size_log_2_ = std::ceil(std::log2(new_base_block_size));
            current_base_block_size_log_log_2_ =  std::ceil(std::log2(current_base_block_size_log_2_));
            locate_mask_ = (1 << current_base_block_size_log_2_) - 1;

            TZA_index_t active_new_power_of_b = 1;
            for(TZA_index_t& power_of_b : new_powers_of_b){
                power_of_b = active_new_power_of_b;
                active_new_power_of_b =  active_new_power_of_b << current_base_block_size_log_2_;
            }

            TZA_index_t redundant_base_block_counter_for_r = 0;
            TZA_index_t type_index = r - 1;
            for(TZA_index_t & r_i : redundant_base_b_counter_){
                r_i = redundant_base_block_counter_for_r + (new_redundant_base_block_representation.at(type_index) * new_powers_of_b.at(type_index));
                redundant_base_block_counter_for_r += (new_redundant_base_block_representation.at(type_index) * new_powers_of_b.at(type_index));
                --type_index;
            }
            std::reverse(redundant_base_b_counter_.begin(), redundant_base_b_counter_.end());
            powers_of_b_ = std::move(new_powers_of_b);

            if(block_type_to_count_map_[0] == 0 && block_type_to_count_map_ [1] == 0){
                SplitBlocks();
            }
        }



        [[nodiscard]] TZA_index_t FindFirstBlockTypeWhichIsNotCompletelyFilled() const{
            TZA_index_t first_block_type_to_check = 2;
            for(TZA_index_t current_block_type = first_block_type_to_check; current_block_type < block_type_to_count_map_.size(); ++ current_block_type){
                if(block_type_to_count_map_[current_block_type] < (2* current_base_block_size_ - 2)){
                    return current_block_type;
                }
            }
            throw std::invalid_argument("Error in code");
        }

        [[nodiscard]] TZA_index_t FindFirstBlockTypeWhichIsNotEmpty() const{
            TZA_index_t first_block_type_to_check = 2;
            for(TZA_index_t current_block_type = first_block_type_to_check; current_block_type < block_type_to_count_map_.size(); ++current_block_type){
                if(block_type_to_count_map_[current_block_type] != 0){
                    return current_block_type;
                }
            }
            if(r == 2){
                if(block_type_to_count_map_[1] > 0){
                    return 1;
                }
            }
            throw std::invalid_argument("Error in code");
        }

        void Copy(T* source_block_address, TZA_index_t source_start, T* destination_block_address, TZA_index_t destination_start,
                  TZA_index_t length){
            for(TZA_index_t current_length = 0; current_length < length; ++current_length){
                T temp = source_block_address[source_start + current_length];
                destination_block_address[destination_start + current_length] = temp;
            }
        }

        void CombineBlocks(){

            TZA_index_t first_unfilled_block_type_index = FindFirstBlockTypeWhichIsNotCompletelyFilled();
            TZA_index_t  max_items_in_block = (current_base_block_size_ << 1) - 2;

            for(TZA_index_t current_block_type_index = first_unfilled_block_type_index - 1;
            current_block_type_index >= 1; --current_block_type_index){
                TZA_index_t current_block_type_size = powers_of_b_[current_block_type_index];
                TZA_index_t block_size_of_destination = current_block_type_size << current_base_block_size_log_2_;
                index_blocks_list_[current_block_type_index + 1].push_back(Allocate(block_size_of_destination));
                T* destination_block_start_address = index_blocks_list_[current_block_type_index + 1].back();
                for(TZA_index_t block_index = 0; block_index < current_base_block_size_; ++block_index){
                    T* source_block_address = index_blocks_list_[current_block_type_index][block_index];
                    Copy(source_block_address, 0, destination_block_start_address, (current_block_type_size * block_index), current_block_type_size);
                    DeAllocate(source_block_address, current_block_type_size);
                    if(block_index + current_base_block_size_ < max_items_in_block)
                        index_blocks_list_[current_block_type_index][block_index] = index_blocks_list_[current_block_type_index][block_index + current_base_block_size_];
                }
                index_blocks_list_[current_block_type_index].resize(current_base_block_size_ - 2);
                ++block_type_to_count_map_[current_block_type_index + 1];
                redundant_base_b_counter_[current_block_type_index + 1]  += powers_of_b_[current_block_type_index + 1];
                block_type_to_count_map_[current_block_type_index] = current_base_block_size_ - 2;
            }
            if(block_type_to_count_map_.at(0) > current_base_block_size_){
                 T* destination_block_address = index_blocks_list_[0][0];
                 index_blocks_list_[1].push_back(destination_block_address);
                 index_blocks_list_[0][0] = index_blocks_list_[0][1];
                 index_blocks_list_[0].resize(1);
                 block_type_to_count_map_[0] = current_base_block_size_ - 2;
                 ++block_type_to_count_map_[1];
                 redundant_base_b_counter_[1] += current_base_block_size_;
            }
        }

        void SplitBlocks(){
            TZA_index_t first_non_empty_block_type_index = FindFirstBlockTypeWhichIsNotEmpty();

            for(TZA_index_t current_block_type_id = first_non_empty_block_type_index - 1; current_block_type_id >= 1; --current_block_type_id){
                TZA_index_t current_block_size = powers_of_b_[current_block_type_id];
                TZA_index_t last_block_position_for_higher_block_type = block_type_to_count_map_.at(current_block_type_id + 1) - 1;
                T* higher_block_address = index_blocks_list_[current_block_type_id + 1][last_block_position_for_higher_block_type];
                for(TZA_index_t block_position = 0;  block_position < current_base_block_size_; ++block_position){
                    T* block_start_address = Allocate(current_block_size);
                    index_blocks_list_.at(current_block_type_id).push_back(block_start_address);
                    Copy(higher_block_address, block_position * current_block_size, block_start_address, 0, current_block_size);
                }
                --block_type_to_count_map_.at(current_block_type_id + 1);
                redundant_base_b_counter_[current_block_type_id + 1] -= (current_block_size << current_base_block_size_log_2_);
                DeAllocate(higher_block_address, current_block_size << current_base_block_size_log_2_);
                index_blocks_list_.at(current_block_type_id + 1).pop_back();
                block_type_to_count_map_.at(current_block_type_id) = current_base_block_size_;
            }

                index_blocks_list_[0].push_back(index_blocks_list_[1].back());
                index_blocks_list_[1].pop_back();
                block_type_to_count_map_[0] = current_base_block_size_;
                --block_type_to_count_map_[1];
                redundant_base_b_counter_[1] -= current_base_block_size_;

        }

    public:

        explicit TarjanAndZewicksOptimalArray() : current_base_block_size_(initial_block_size), size_(0),
                                                  standardBaseBCounter_(current_base_block_size_, r){
            current_base_block_size_power_r_ = std::pow(current_base_block_size_, r);

            redundant_base_b_counter_.resize(r, 0);
            current_base_block_size_log_2_ = std::ceil(std::log2(current_base_block_size_));
            current_base_block_size_log_log_2_ =  std::ceil(std::log2(current_base_block_size_log_2_));
            locate_mask_ = (1 << current_base_block_size_log_2_) - 1;
            current_base_block_size_ = std::pow(2, current_base_block_size_log_2_);
            current_base_block_size_division_four_power_r_ = std::pow((current_base_block_size_ / 4), r);
            block_type_to_count_map_.resize(r, 0);
            index_blocks_list_.resize(r);
            powers_of_b_.resize(r);
            TZA_index_t current_power_of_b = 1;
            for(TZA_index_t& power_of_B : powers_of_b_){
                power_of_B = current_power_of_b;
                current_power_of_b =  current_power_of_b << current_base_block_size_log_2_;
            }

        }

        const T& Locate(TZA_index_t index) const{
            TZA_index_t  N_minus_i = size_ - index;
            // msb position starts from 0.
            TZA_index_t msb_N_minus_i = GetMSB(N_minus_i);
            TZA_index_t Nk = (msb_N_minus_i)/(current_base_block_size_log_2_);
            if(index < redundant_base_b_counter_[Nk]){
                TZA_index_t current_block_size_log_2 = current_base_block_size_log_2_ * (Nk);
                TZA_index_t Nr_plus_one = 0;
                if(Nk < r - 1){
                    Nr_plus_one = redundant_base_b_counter_[Nk + 1];
                }
                while(index < Nr_plus_one){
                    ++Nk;
                    if(Nk < r - 1)
                        Nr_plus_one = redundant_base_b_counter_[Nk + 1];
                    else{
                        Nr_plus_one = 0;
                    }
                    current_block_size_log_2 += current_base_block_size_log_2_;
                }
                if(Nk > 0) {
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                    TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                    return index_blocks_list_[Nk][block_position][element_position];
                }
                else{
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                    TZA_index_t element_position = relative_index & ((1 << current_base_block_size_log_2_) - 1);
                    return index_blocks_list_[Nk][block_position][element_position];
                }
            }
            else {
                TZA_index_t Nr_plus_one = redundant_base_b_counter_[Nk];
                TZA_index_t current_block_size_log_2 = current_base_block_size_log_2_ * (Nk - 1);
                for (int block_type = Nk - 1; block_type >= 0; --block_type) {
                    TZA_index_t Nr = redundant_base_b_counter_[block_type];
                    if (index < Nr && block_type > 0) {
                        TZA_index_t relative_index = index - Nr_plus_one;
                        TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                        TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                        return index_blocks_list_[block_type][block_position][element_position];
                    } else if (block_type == 0) {
                        TZA_index_t relative_index = index - Nr_plus_one;
                        TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                        TZA_index_t element_position = relative_index & ((1 << current_base_block_size_log_2_) - 1);
                        return index_blocks_list_[block_type][block_position][element_position];
                    }
                    Nr_plus_one = Nr;
                    current_block_size_log_2 -= current_base_block_size_log_2_;
                }
            }
            throw std::invalid_argument("Invalid Index");
        }

        T& Locate(TZA_index_t index){
            TZA_index_t  N_minus_i = size_ - index;
            // msb position starts from 0.
            TZA_index_t msb_N_minus_i = GetMSB(N_minus_i);
            TZA_index_t Nk = (msb_N_minus_i)/(current_base_block_size_log_2_);
            if(index < redundant_base_b_counter_[Nk]){
                TZA_index_t current_block_size_log_2 = current_base_block_size_log_2_ * (Nk);
                TZA_index_t Nr_plus_one = 0;
                if(Nk < r - 1){
                    Nr_plus_one = redundant_base_b_counter_[Nk + 1];
                }
                while(index < Nr_plus_one){
                    ++Nk;
                    if(Nk < r - 1)
                        Nr_plus_one = redundant_base_b_counter_[Nk + 1];
                    else{
                        Nr_plus_one = 0;
                    }
                    current_block_size_log_2 += current_base_block_size_log_2_;
                }
                if(Nk > 0) {
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                    TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                    return index_blocks_list_[Nk][block_position][element_position];
                }
                else{
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                    TZA_index_t element_position = relative_index & ((1 << current_base_block_size_log_2_) - 1);
                    return index_blocks_list_[Nk][block_position][element_position];
                }
            }
            else {
                TZA_index_t Nr_plus_one = redundant_base_b_counter_[Nk];
                TZA_index_t current_block_size_log_2 = current_base_block_size_log_2_ * (Nk - 1);
                for (int block_type = Nk - 1; block_type >= 0; --block_type) {
                    TZA_index_t Nr = redundant_base_b_counter_[block_type];
                    if (index < Nr && block_type > 0) {
                        TZA_index_t relative_index = index - Nr_plus_one;
                        TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                        TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                        return index_blocks_list_[block_type][block_position][element_position];
                    } else if (block_type == 0) {
                        TZA_index_t relative_index = index - Nr_plus_one;
                        TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                        TZA_index_t element_position = relative_index & ((1 << current_base_block_size_log_2_) - 1);
                        return index_blocks_list_[block_type][block_position][element_position];
                    }
                    Nr_plus_one = Nr;
                    current_block_size_log_2 -= current_base_block_size_log_2_;
                }
            }
            throw std::invalid_argument("Invalid Index");
        }

        T& LocateNew(TZA_index_t index){
            TZA_index_t  N_minus_i = size_ - index;
            // msb position starts from 0.
            TZA_index_t msb_N_minus_i = GetMSB(N_minus_i);
            TZA_index_t Nk = (msb_N_minus_i) / (current_base_block_size_log_2_);
            if(index < redundant_base_b_counter_[Nk]){
                TZA_index_t current_block_size_log_2 = (Nk) * current_base_block_size_log_2_;
                TZA_index_t Nr_plus_one = 0;
                if(Nk < r - 1){
                    Nr_plus_one = redundant_base_b_counter_[Nk + 1];
                }
                if(Nk > 0) {
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                    TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                    //TZA_index_t element_position = relative_index & masks_[Nk];
                    return index_blocks_list_[Nk][block_position][element_position];
                }
                else{
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                    TZA_index_t element_position = relative_index & locate_mask_;
                    return index_blocks_list_[Nk][block_position][element_position];
                }
            }
            else {
                TZA_index_t Nr_plus_one = redundant_base_b_counter_[Nk];
                TZA_index_t current_block_size_log_2 = (Nk - 1) * current_base_block_size_log_2_;
                for (int block_type = Nk - 1; block_type >= 0; --block_type) {
                    TZA_index_t Nr = redundant_base_b_counter_[block_type];
                    if (index < Nr && block_type > 0) {
                        TZA_index_t relative_index = index - Nr_plus_one;
                        TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                        TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                        //TZA_index_t element_position = relative_index & masks_[block_type];
                        return index_blocks_list_[block_type][block_position][element_position];
                    } else if (block_type == 0) {
                        TZA_index_t relative_index = index - Nr_plus_one;
                        TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                        TZA_index_t element_position = relative_index & (locate_mask_);
                        return index_blocks_list_[block_type][block_position][element_position];
                    }
                    Nr_plus_one = Nr;
                    current_block_size_log_2 -= current_base_block_size_log_2_;
                }
            }
            throw std::invalid_argument("invalid index");
        }

        const T& LocateNew(TZA_index_t index) const {
            TZA_index_t  N_minus_i = size_ - index;
            // msb position starts from 0.
            TZA_index_t msb_N_minus_i = GetMSB(N_minus_i);
            TZA_index_t Nk = (msb_N_minus_i) / (current_base_block_size_log_2_);
            if(index < redundant_base_b_counter_[Nk]){
                TZA_index_t current_block_size_log_2 = (Nk) * current_base_block_size_log_2_;
                TZA_index_t Nr_plus_one = 0;
                if(Nk < r - 1){
                    Nr_plus_one = redundant_base_b_counter_[Nk + 1];
                }
                if(Nk > 0) {
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                    TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                    //TZA_index_t element_position = relative_index & masks_[Nk];
                    return index_blocks_list_[Nk][block_position][element_position];
                }
                else{
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                    TZA_index_t element_position = relative_index & locate_mask_;
                    return index_blocks_list_[Nk][block_position][element_position];
                }
            }
            else {
                TZA_index_t Nr_plus_one = redundant_base_b_counter_[Nk];
                TZA_index_t current_block_size_log_2 = (Nk - 1) * current_base_block_size_log_2_;
                for (int block_type = Nk - 1; block_type >= 0; --block_type) {
                    TZA_index_t Nr = redundant_base_b_counter_[block_type];
                    if (index < Nr && block_type > 0) {
                        TZA_index_t relative_index = index - Nr_plus_one;
                        TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                        TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                        //TZA_index_t element_position = relative_index & masks_[block_type];
                        return index_blocks_list_[block_type][block_position][element_position];
                    } else if (block_type == 0) {
                        TZA_index_t relative_index = index - Nr_plus_one;
                        TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                        TZA_index_t element_position = relative_index & (locate_mask_);
                        return index_blocks_list_[block_type][block_position][element_position];
                    }
                    Nr_plus_one = Nr;
                    current_block_size_log_2 -= current_base_block_size_log_2_;
                }
            }
            throw std::invalid_argument("invalid index");
        }

        T& operator[](std::size_t index) {
            return Locate(index);
        }

        const T& operator[](std::size_t index) const {
            return Locate(index);
        }




        const T& LocateWithoutMSB(TZA_index_t index) const{
            //TZA_index_t  N_minus_i = size_ - index;
            //TZA_index_t msb_N_minus_i = GetMSB(N_minus_i);
            //TZA_index_t Nk = (msb_N_minus_i)/(current_base_block_size_log_2_);
            TZA_index_t Nr_plus_one = 0;
            TZA_index_t current_block_size_log_2 = current_base_block_size_log_2_ * (r - 1);
            //TZA_index_t mask = (1 << current_block_size_log_2) - 1;
            for(int block_type = r - 1; block_type >= 0; --block_type){
                TZA_index_t Nr = redundant_base_b_counter_[block_type];
                if(index < Nr && block_type > 0){
                   TZA_index_t relative_index = index - Nr_plus_one;
                   TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                   TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                   return index_blocks_list_[block_type][block_position][element_position];
                }
                else if(block_type == 0){
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                    TZA_index_t element_position = relative_index & (( 1<< current_base_block_size_log_2_) - 1);
                    return index_blocks_list_[block_type][block_position][element_position];
                }
                Nr_plus_one= Nr;
                current_block_size_log_2 -= current_base_block_size_log_2_;
            }
            throw std::invalid_argument("invalid index");
        }

        T& LocateWithoutMSB(TZA_index_t index){
            //TZA_index_t  N_minus_i = size_ - index;
            //TZA_index_t msb_N_minus_i = GetMSB(N_minus_i);
            //TZA_index_t Nk = (msb_N_minus_i)/(current_base_block_size_log_2_);
            TZA_index_t Nr_plus_one = 0;
            TZA_index_t current_block_size_log_2 = current_base_block_size_log_2_ * (r - 1);
            //TZA_index_t mask = (1 << current_block_size_log_2) - 1;
            for(int block_type = r - 1; block_type >= 0; --block_type){
                TZA_index_t Nr = redundant_base_b_counter_[block_type];
                if(index < Nr && block_type > 0){
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> (current_block_size_log_2);
                    TZA_index_t element_position = relative_index & ((1 << current_block_size_log_2) - 1);
                    return index_blocks_list_[block_type][block_position][element_position];
                }
                else if(block_type == 0){
                    TZA_index_t relative_index = index - Nr_plus_one;
                    TZA_index_t block_position = relative_index >> current_base_block_size_log_2_;
                    TZA_index_t element_position = relative_index & (( 1<< current_base_block_size_log_2_) - 1);
                    return index_blocks_list_[block_type][block_position][element_position];
                }
                Nr_plus_one= Nr;
                current_block_size_log_2 -= current_base_block_size_log_2_;
            }
            throw std::invalid_argument("invalid index");
        }

        void PushBack(const T& item){

            TZA_index_t max_items_in_block = (current_base_block_size_ << 1) - 2;
            TZA_index_t  number_of_blocks_at_type_zero = block_type_to_count_map_[0];
            TZA_index_t  number_of_blocks_at_type_one = block_type_to_count_map_[1];

            if(size_ == current_base_block_size_power_r_){
                Rebuild3(default_growth_factor);
                max_items_in_block = (current_base_block_size_ << 1) - 2;
                number_of_blocks_at_type_zero = block_type_to_count_map_[0];
                number_of_blocks_at_type_one = block_type_to_count_map_[1];
            }

            else if(number_of_blocks_at_type_one == max_items_in_block  && number_of_blocks_at_type_zero == max_items_in_block){
                CombineBlocks();
                number_of_blocks_at_type_zero = block_type_to_count_map_[0];
                number_of_blocks_at_type_one = block_type_to_count_map_[1];
            }

            if(number_of_blocks_at_type_zero < max_items_in_block) {
                if(number_of_blocks_at_type_zero == current_base_block_size_ || number_of_blocks_at_type_zero == 0) {
                    if (is_empty_block_present) {
                        index_blocks_list_[0].push_back(empty_block);
                        is_empty_block_present = false;
                    } else {
                        index_blocks_list_[0].push_back(Allocate(current_base_block_size_));
                    }
                }
            }
            else{
                index_blocks_list_[1].push_back(index_blocks_list_[0].front());
                redundant_base_b_counter_[1] += powers_of_b_.at(1);
                index_blocks_list_[0][0] = index_blocks_list_[0][1];
                index_blocks_list_[0].resize(1);
                ++block_type_to_count_map_[1];
                block_type_to_count_map_[0] = current_base_block_size_ - 2;
            }

            TZA_index_t n0 = block_type_to_count_map_[0] & ((1 << current_base_block_size_log_2_) - 1);
            index_blocks_list_[0].back()[n0] = item;
            ++redundant_base_b_counter_.at(0);
            ++block_type_to_count_map_.at(0);
            ++size_;

            if(size_ == current_base_block_size_power_r_){
                Rebuild3(default_growth_factor);
            }
        }

        void PopBack(){

            if(size_ == 0){
                return;
            }
            if(size_ == current_base_block_size_division_four_power_r_ && current_base_block_size_ > initial_block_size){
                Rebuild3(1.0/default_growth_factor);
            }
            if(block_type_to_count_map_[1] == 0 && block_type_to_count_map_[0] == 0){
                SplitBlocks();
            }


            if(block_type_to_count_map_[0] == 0){
                index_blocks_list_[0].push_back((index_blocks_list_[1].back()));
                index_blocks_list_[1].pop_back();
                block_type_to_count_map_[0] = current_base_block_size_;
                --block_type_to_count_map_[1];
                redundant_base_b_counter_[1] -= current_base_block_size_;
            }


            --block_type_to_count_map_[0];
            --size_;
            --redundant_base_b_counter_[0];
            if(block_type_to_count_map_[0] == 0 || block_type_to_count_map_[0] == current_base_block_size_){
               if(is_empty_block_present){
                   DeAllocate(empty_block, current_base_block_size_);
               }
               empty_block = index_blocks_list_[0].back();
               index_blocks_list_[0].pop_back();
               is_empty_block_present = true;
            }

            if(size_ == current_base_block_size_division_four_power_r_ && current_base_block_size_ > initial_block_size){
                Rebuild3(1.0/default_growth_factor);
            }

        }

        [[nodiscard]] TZA_index_t Size() const{
            return size_;
        }

        StateFullReadReverseIterator<T, r>  GetStateFullReadReverseIterator() const{
            return StateFullReadReverseIterator<T,r>{block_type_to_count_map_, index_blocks_list_, powers_of_b_, size_};
        }

        StateFullReadIterator<T, r>  GetStateFullReadIterator() const{
            return StateFullReadIterator<T,r>{block_type_to_count_map_, index_blocks_list_, powers_of_b_, size_};
        }



        ~TarjanAndZewicksOptimalArray(){

            for(auto & block_list : index_blocks_list_){
                for(T* block_start_pointer : block_list){
                    delete [] block_start_pointer;
                }
            }
            if(is_empty_block_present){
                DeAllocate(empty_block, current_base_block_size_);
            }
        }

    public:

        class iterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T *;
            using reference = T &;

            // Default constructor
            iterator() : container_(nullptr), index_(0) {}

            // Constructor taking a pointer to the container and an index
            iterator(TarjanAndZewicksOptimalArray<T,r, initial_block_size> *container, std::size_t index) : container_(container),
                                                                              index_(index) {}

            // Dereference operator
            reference operator*() const {
                return (*container_)[index_];
            }

            // Member access operator
            pointer operator->() const {
                return &(*container_)[index_];
            }

            // Prefix increment operator
            iterator &operator++() {
                ++index_;
                return *this;
            }

            // Postfix increment operator
            iterator operator++(int) {
                iterator tmp = *this;
                ++index_;
                return tmp;
            }

            // Prefix decrement operator
            iterator &operator--() {
                --index_;
                return *this;
            }

            // Postfix decrement operator
            iterator operator--(int) {
                iterator tmp = *this;
                --index_;
                return tmp;
            }

            // Addition operator
            iterator operator+(difference_type n) const {
                return iterator(container_, index_ + n);
            }

            // Subtraction operator
            iterator operator-(difference_type n) const {
                return iterator(container_, index_ - n);
            }

            // Compound assignment addition operator
            iterator &operator+=(difference_type n) {
                index_ += n;
                return *this;
            }

            // Compound assignment subtraction operator
            iterator &operator-=(difference_type n) {
                index_ -= n;
                return *this;
            }

            // Difference operator
            difference_type operator-(const iterator &other) const {
                return index_ - other.index_;
            }

            // Equality operator
            bool operator==(const iterator &other) const {
                return container_ == other.container_ && index_ == other.index_;
            }

            // Inequality operator
            bool operator!=(const iterator &other) const {
                return !(*this == other);
            }

            // Less than operator
            bool operator<(const iterator &other) const {
                return index_ < other.index_;
            }

            // Less than or equal to operator
            bool operator<=(const iterator &other) const {
                return index_ <= other.index_;
            }

            // Greater than operator
            bool operator>(const iterator &other) const {
                return index_ > other.index_;
            }

            // Greater than or equal to operator
            bool operator>=(const iterator &other) const {
                return index_ >= other.index_;
            }

        private:
            TarjanAndZewicksOptimalArray<T, r, initial_block_size> *container_;
            std::size_t index_ = 0;
        };

        iterator begin(){
            return iterator(this, 0);
        }
        iterator end(){
            return  iterator(this, size_);
        }
    };



};




#endif //RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_H
