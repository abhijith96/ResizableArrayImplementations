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
#include <array>

namespace TarjanAndZewicksOptimalArrayRGrows{

    constexpr TZA_index_t default_r = 4;
    constexpr double default_growth_factor = 2;
    constexpr int default_block_size = 4;

    template<class T, TZA_index_t initial_r = default_r, TZA_index_t initial_block_size = default_block_size>


    class TarjanAndZewicksOptimalArray {
        TZA_index_t r_;
        std::vector<TZA_index_t> block_type_to_count_map_;
        std::vector<std::vector<T*>> index_blocks_list_;
        std::array<TZA_index_t , 64> powers_of_b_;
        std::array<TZA_index_t , 64> masks_;
        std::array<TZA_index_t , 64> redundant_base_b_counter_;
        TZA_index_t current_base_block_size_;
        TZA_index_t size_;
        TZA_index_t current_base_block_size_power_r_;
        TZA_index_t current_base_block_size_log_2_;
        TZA_index_t current_base_block_size_log_log_log_2_;
        TZA_index_t current_base_block_size_division_four_power_r_;
        TZA_index_t locate_mask_;
        T* empty_block = nullptr;
        bool is_empty_block_present = false;

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

        void GrowR(){
            current_base_block_size_power_r_ =  current_base_block_size_power_r_ << current_base_block_size_log_2_;
            ++r_;
            current_base_block_size_division_four_power_r_  =  current_base_block_size_division_four_power_r_ = std::pow(current_base_block_size_/4, r_);
            if(current_base_block_size_division_four_power_r_ == 0){
                current_base_block_size_division_four_power_r_ = 1;
            }
            block_type_to_count_map_.push_back(0);
            index_blocks_list_.push_back(std::vector<T*>{});
            redundant_base_b_counter_[r_ - 1] = 0;
        }

        void ShrinkR(){
            if(block_type_to_count_map_[0] == 0 && block_type_to_count_map_[1] == 0){
                SplitBlocks();
            }
            if(block_type_to_count_map_[r_ - 1] == 0 && block_type_to_count_map_ [r_ - 2] == 0 && r_ > initial_r) {
                block_type_to_count_map_.pop_back();
                --r_;
                current_base_block_size_power_r_ >>= current_base_block_size_log_2_;
                current_base_block_size_division_four_power_r_ = current_base_block_size_division_four_power_r_  =  current_base_block_size_division_four_power_r_ = std::pow(current_base_block_size_/4, r_);
                if (current_base_block_size_division_four_power_r_ == 0) {
                    current_base_block_size_division_four_power_r_ = 1;
                }
                index_blocks_list_.pop_back();
                redundant_base_b_counter_[r_] = 0;
            }
        }

    public:

        explicit TarjanAndZewicksOptimalArray() : r_(initial_r), current_base_block_size_(std::max(initial_block_size,static_cast<TZA_index_t>(4))), size_(0)
                                                 {
            current_base_block_size_power_r_ = std::pow(current_base_block_size_, r_);
            current_base_block_size_log_2_ = std::ceil(std::log2(current_base_block_size_));
            current_base_block_size_log_log_log_2_ = std::ceil(std::log2(current_base_block_size_log_2_));
            current_base_block_size_ = std::pow(2, current_base_block_size_log_2_);
            current_base_block_size_division_four_power_r_ = std::pow((current_base_block_size_ / 4), r_);
            block_type_to_count_map_.resize(r_, 0);
            index_blocks_list_.resize(r_);
            TZA_index_t current_power_of_b = 1;
            for(TZA_index_t& power_of_B : powers_of_b_){
                power_of_B = current_power_of_b;
                current_power_of_b =  current_power_of_b << current_base_block_size_log_2_;
            }
            locate_mask_ = (1 << current_base_block_size_log_2_) - 1;
            for(TZA_index_t& item : redundant_base_b_counter_){
                item = 0;
            }
            TZA_index_t  current_block_size_log_2 = current_base_block_size_log_2_;
            masks_[0] = locate_mask_;
            TZA_index_t current_block_type = 1;
            while(current_block_size_log_2 < 63){
                TZA_index_t current_mask = (1 << current_block_size_log_2) - 1;
                masks_[current_block_type] = current_mask;
                current_block_size_log_2 += current_base_block_size_log_2_;
                ++current_block_type;
            }

        }

        const T& LocateNew(TZA_index_t index) const{
            TZA_index_t  N_minus_i = size_ - index;
            // msb position starts from 0.
            TZA_index_t msb_N_minus_i = GetMSB(N_minus_i);
            TZA_index_t Nk = (msb_N_minus_i) >> (current_base_block_size_log_log_log_2_);
            if(index < redundant_base_b_counter_[Nk]){
                TZA_index_t current_block_size_log_2 = (Nk) << current_base_block_size_log_log_log_2_;
                TZA_index_t Nr_plus_one = 0;
                if(Nk < r_ - 1){
                    Nr_plus_one = redundant_base_b_counter_[Nk + 1];
                }
//                while(index < Nr_plus_one){
//                    ++Nk;
//                    if(Nk < r_ - 1)
//                        Nr_plus_one = redundant_base_b_counter_[Nk + 1];
//                    else{
//                        Nr_plus_one = 0;
//                    }
//                    current_block_size_log_2 += current_base_block_size_log_2_;
//                }
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
                TZA_index_t current_block_size_log_2 = (Nk - 1) << current_base_block_size_log_log_log_2_;
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
            return 0;
        }

         T Locate(TZA_index_t index) const{
            TZA_index_t Nr_plus_one = 0;
            TZA_index_t current_block_size_log_2 = current_base_block_size_log_2_ * (r_ - 1);
            for(int block_type = r_ - 1; block_type >= 0; --block_type){
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
            return 0;
        }

        void PushBack(const T& item){



            if(size_ == current_base_block_size_power_r_){
               GrowR();
            }
            TZA_index_t max_items_in_block = (current_base_block_size_ << 1) - 2;
            TZA_index_t  number_of_blocks_at_type_zero = block_type_to_count_map_[0];
            TZA_index_t  number_of_blocks_at_type_one = block_type_to_count_map_[1];

            if(number_of_blocks_at_type_one == max_items_in_block  && number_of_blocks_at_type_zero == max_items_in_block){
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

            TZA_index_t n0 = block_type_to_count_map_[0] & (locate_mask_);
            index_blocks_list_[0].back()[n0] = item;
            ++redundant_base_b_counter_.at(0);
            ++block_type_to_count_map_.at(0);
            ++size_;

            if(size_ == current_base_block_size_power_r_){
               GrowR();
               if(block_type_to_count_map_[0] == max_items_in_block && block_type_to_count_map_[1] == max_items_in_block){
                   CombineBlocks();
               }
            }
        }

        void PopBack(){

            if(size_ == 0){
                return;
            }
            if(size_ == current_base_block_size_division_four_power_r_ && current_base_block_size_ > initial_block_size){
                ShrinkR();
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
                ShrinkR();
                if(block_type_to_count_map_[0] == 0 && block_type_to_count_map_[1] == 0){
                    SplitBlocks();
                }
            }

        }

        [[nodiscard]] TZA_index_t Size() const{
            return size_;
        }

        StateFullReadReverseIterator<T>  GetStateFullReadReverseIterator() const{
            return StateFullReadReverseIterator<T>{r_, block_type_to_count_map_, index_blocks_list_, powers_of_b_, size_};
        }

        StateFullReadIterator<T>  GetStateFullReadIterator() const{
            return StateFullReadIterator<T>{r_, block_type_to_count_map_, index_blocks_list_, powers_of_b_, size_};
        }

        [[nodiscard]] TZA_index_t GetCurrentRValue() const{
            return r_;
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


    };


}


#endif //RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_H
