//
// Created by Abhijith  K A on 30/03/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_H
#define RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_H

#include "Constants.h"
#include <vector>
#include <cmath>

namespace TarjanAndZewicksOptimalArray{

    constexpr TZA_index_t default_r = 4;
    constexpr double default_growth_factor = 2;
    constexpr int default_block_size = 4;

    template<class T, TZA_index_t r = default_r, TZA_index_t initial_block_size = default_block_size>


    class TarjanAndZewicksOptimalArray {
        std::vector<TZA_index_t> block_type_to_count_map_;
        std::vector<std::vector<T*>> index_blocks_list_;
        TZA_index_t current_base_block_size_;
        TZA_index_t size_;
        TZA_index_t current_base_block_size_power_r_;
        TZA_index_t current_base_block_size_division_four_power_r_;
        T* empty_block = nullptr;
        bool is_empty_block_present = false;

        T* Allocate(TZA_index_t block_size){
            return new T[block_size];
        }
        void DeAllocate(T* block_pointer, [[maybe_unused]] TZA_index_t block_size){
            delete[] block_pointer;
        }

        void Rebuild(double growth_factor) {
            TZA_index_t new_base_block_size = std::ceil(current_base_block_size_ * growth_factor);
            TZA_index_t new_base_block_size_power_r = std::pow(new_base_block_size, r);
            TZA_index_t elements_left_to_copy = size_;

            TZA_index_t active_old_block_type_id = r - 1;
            TZA_index_t active_old_block_index_in_old_block_type = 0;
            TZA_index_t active_old_element_index_in_active_old_block = 0;
            TZA_index_t active_old_block_id_block_size = current_base_block_size_power_r_ / current_base_block_size_;
            TZA_index_t block_count_in_active_old_block_id = block_type_to_count_map_.at(r - 1);

            if(is_empty_block_present){
                DeAllocate(empty_block, current_base_block_size_);
            }
            is_empty_block_present = false;


            std::vector<TZA_index_t> new_block_type_to_count_map(r, 0);


            TZA_index_t active_new_block_type_id = r - 1;
            TZA_index_t block_size_for_active_new_block_id = new_base_block_size_power_r / new_base_block_size;
            TZA_index_t block_count_in_active_new_block_id = 0;



            std::vector<std::vector<T*>> index_list_for_blocks(r);


            while (elements_left_to_copy > 0) {

                if (block_count_in_active_new_block_id > 2 * new_base_block_size) {
                    --active_new_block_type_id;
                    block_size_for_active_new_block_id = active_old_block_id_block_size / new_base_block_size;
                    block_count_in_active_new_block_id = 0;
                }
                else if (block_size_for_active_new_block_id > elements_left_to_copy && active_new_block_type_id > 1) {
                        --active_new_block_type_id;
                        block_size_for_active_new_block_id = block_size_for_active_new_block_id / new_base_block_size;
                        block_count_in_active_new_block_id = 0;
                }
                else {
                    std::vector<T*> & list_for_storing_blocks_in_current_block_id = index_list_for_blocks.at(active_new_block_type_id);
                    T* active_new_block_start_address = Allocate(block_size_for_active_new_block_id);
                    TZA_index_t active_new_elements_in_new_block_index = 0;
                    while(active_new_elements_in_new_block_index < block_size_for_active_new_block_id && elements_left_to_copy > 0){
                        if (active_old_block_type_id < 1) {
                            throw std::invalid_argument(
                                    "error in code old block type id cannot be less than 1 while calling rebuild");
                        } else if (block_count_in_active_old_block_id == 0 ||
                                   active_old_block_index_in_old_block_type >=
                                   block_count_in_active_old_block_id) {
                            --active_old_block_type_id;
                            active_old_block_index_in_old_block_type = 0;
                            active_old_element_index_in_active_old_block = 0;
                            active_old_block_id_block_size =
                                    active_old_block_id_block_size / current_base_block_size_;
                            block_count_in_active_old_block_id = block_type_to_count_map_.at(
                                    active_old_block_type_id);
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
                        new_block_type_to_count_map.at(0) = active_new_elements_in_new_block_index;
                    }
                    if(elements_left_to_copy == 0){
                        if(active_old_block_index_in_old_block_type < block_count_in_active_old_block_id){
                            DeAllocate(index_blocks_list_.at(active_old_block_type_id).at(
                                    active_old_block_index_in_old_block_type), active_old_block_id_block_size);
                        }
                    }
                    ++block_count_in_active_new_block_id;
                    ++new_block_type_to_count_map.at(active_new_block_type_id);
                    list_for_storing_blocks_in_current_block_id.push_back(active_new_block_start_address);
                }
            }

            index_blocks_list_ = std::move(index_list_for_blocks);
            block_type_to_count_map_ = std::move(new_block_type_to_count_map);
            current_base_block_size_ = new_base_block_size;
            current_base_block_size_power_r_ = new_base_block_size_power_r;
            current_base_block_size_division_four_power_r_ = std::pow(new_base_block_size/4, r);

        }



        [[nodiscard]] TZA_index_t FindFirstBlockTypeWhichIsNotCompletelyFilled() const{
            TZA_index_t first_block_type_to_check = 2;
            for(TZA_index_t current_block_type = first_block_type_to_check; current_block_type < block_type_to_count_map_.size(); ++ current_block_type){
                if(block_type_to_count_map_.at(current_block_type) < 2* current_base_block_size_){
                    return current_block_type;
                }
            }
            throw std::invalid_argument("Error in code");
        }

        [[nodiscard]] TZA_index_t FindFirstBlockTypeWhichIsNotEmpty() const{
            TZA_index_t first_block_type_to_check = 2;
            for(TZA_index_t current_block_type = first_block_type_to_check; current_block_type < block_type_to_count_map_.size(); ++ current_block_type){
                if(block_type_to_count_map_.at(current_block_type) != 0){
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
            TZA_index_t first_unfilled_block_type_size = std::pow(current_base_block_size_, first_unfilled_block_type_index);

            TZA_index_t current_block_type_size = first_unfilled_block_type_size;
            for(TZA_index_t current_block_type_index = first_unfilled_block_type_index - 1;
            current_block_type_index >= 1; --current_block_type_index){
                current_block_type_size /= current_base_block_size_;
                index_blocks_list_[current_block_type_index + 1].push_back(Allocate(current_block_type_size * current_base_block_size_));
                T* destination_block_start_address = index_blocks_list_.at(current_block_type_index + 1).back();
                for(TZA_index_t block_index = 0; block_index < current_base_block_size_; ++block_index){
                    T* source_block_address = index_blocks_list_.at(current_block_type_index).at(block_index);
                    Copy(source_block_address, 0, destination_block_start_address, (current_block_type_size*block_index), current_block_type_size);
                    DeAllocate(source_block_address, current_block_type_size);
                    index_blocks_list_.at(current_block_type_index).at(block_index) = index_blocks_list_.at(current_block_type_index).at(block_index + current_base_block_size_);
                }
                index_blocks_list_.at(current_block_type_index).resize(current_base_block_size_);
                ++block_type_to_count_map_.at(current_block_type_index + 1);
                block_type_to_count_map_.at(current_block_type_index) = current_base_block_size_;
            }
        }

        void SplitBlocks(){
            TZA_index_t first_non_empty_block_type_index = FindFirstBlockTypeWhichIsNotEmpty();
            TZA_index_t first_unfilled_block_type_size = std::pow(current_base_block_size_, first_non_empty_block_type_index);
            TZA_index_t current_block_size = first_unfilled_block_type_size;
            for(TZA_index_t current_block_type_id = first_non_empty_block_type_index - 1; current_block_type_id >= 1; --current_block_type_id){
                current_block_size /= current_base_block_size_;
                TZA_index_t last_block_position_for_higher_block_type = block_type_to_count_map_.at(current_block_type_id + 1) - 1;
                T* higher_block_address = index_blocks_list_.at(current_block_type_id + 1).at(last_block_position_for_higher_block_type);
                for(TZA_index_t block_position = 0;  block_position < current_base_block_size_; ++block_position){
                    T* block_start_address = Allocate(current_block_size);
                    index_blocks_list_.at(current_block_type_id).push_back(block_start_address);
                    Copy(higher_block_address, block_position * current_block_size, block_start_address, 0, current_block_size);
                }
                --block_type_to_count_map_.at(current_block_type_id + 1);
                DeAllocate(higher_block_address, current_block_size * current_base_block_size_);
                index_blocks_list_.at(current_block_type_id + 1).pop_back();
                block_type_to_count_map_.at(current_block_type_id) = current_base_block_size_;
            }
        }

    public:

        explicit TarjanAndZewicksOptimalArray() : current_base_block_size_(initial_block_size), size_(0){
            current_base_block_size_power_r_ = std::pow(current_base_block_size_, r);
            current_base_block_size_division_four_power_r_ = std::pow((current_base_block_size_ / 4), r);
            block_type_to_count_map_.resize(r, 0);
            index_blocks_list_.resize(r);
        }

        const T& Locate(TZA_index_t index){
            if(index  >= size_){
                throw std::invalid_argument("index out of range");
            }
            TZA_index_t  total_items_so_far = 0;
            TZA_index_t current_block_size = current_base_block_size_power_r_/current_base_block_size_;
            TZA_index_t current_block_type = r - 1;
            for(auto iter = block_type_to_count_map_.rbegin(); iter != block_type_to_count_map_.rend(); ++iter){
                TZA_index_t items_with_block_size = *iter;
                TZA_index_t items_in_block = items_with_block_size * current_block_size;
                if(index < (total_items_so_far + items_in_block)){
                    TZA_index_t  relative_index = index - (total_items_so_far);
                    TZA_index_t block_index = relative_index/current_block_size;
                    TZA_index_t element_index = relative_index % current_block_size;
                    return index_blocks_list_.at(current_block_type).at(block_index)[element_index];
                }
                --current_block_type;
                current_block_size/= current_base_block_size_;
                total_items_so_far += items_in_block;
            }
        }

        void PushBack(const T& item){

            if(size_ == current_base_block_size_power_r_){
                Rebuild(default_growth_factor);
            }

            else if(block_type_to_count_map_.at(1) == 2 * current_base_block_size_ && block_type_to_count_map_.at(0) == current_base_block_size_){
                CombineBlocks();
            }

            if(block_type_to_count_map_.at(0) == current_base_block_size_ || block_type_to_count_map_.at(0) == 0) {
                if (is_empty_block_present) {
                    index_blocks_list_.at(1).push_back(empty_block);
                    is_empty_block_present = false;
                }
                else {
                    index_blocks_list_.at(1).push_back(Allocate(current_base_block_size_));
                }
                ++block_type_to_count_map_.at(1);
                block_type_to_count_map_.at(0) = 0;
            }

            TZA_index_t n0 = block_type_to_count_map_.at(0);
            index_blocks_list_.at(1).back()[n0] = item;
            ++block_type_to_count_map_.at(0);
            ++size_;
        }

        void PopBack(){

            if(size_ == 0){
                return;
            }
            if(size_ == current_base_block_size_division_four_power_r_ && current_base_block_size_ > initial_block_size){
                Rebuild(1.0/default_growth_factor);
            }
            else if(block_type_to_count_map_.at(1) == 0){
                SplitBlocks();
            }
            if(block_type_to_count_map_.at(0) == 0){
                block_type_to_count_map_.at(0) = current_base_block_size_;
            }

            --block_type_to_count_map_.at(0);
            --size_;
            if(block_type_to_count_map_.at(0) == 0){
               --block_type_to_count_map_.at(1);
               block_type_to_count_map_.at(0) = block_type_to_count_map_.at(1) > 0 ? current_base_block_size_ : 0;
               if(is_empty_block_present){
                   DeAllocate(empty_block, current_base_block_size_);
               }
               empty_block = index_blocks_list_.at(1).at(block_type_to_count_map_.at(1));
               is_empty_block_present = true;
                //DeAllocate(index_blocks_list_.at(1).at(block_type_to_count_map_.at(1)), current_base_block_size_);
                index_blocks_list_.at(1).pop_back();
            }

        }

        [[nodiscard]] TZA_index_t Size() const{
            return size_;
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
