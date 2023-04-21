//
// Created by Abhijith  K A on 11/04/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_STATEFULLREADREVERSEWITHDELETEBLOCKITERATOR_H
#define RESIZABLEARRAYIMPLEMENTATIONS_STATEFULLREADREVERSEWITHDELETEBLOCKITERATOR_H



#include "Constants.h"
#include <vector>
#include <cmath>

namespace TarjanAndZewicksOptimalArrayLocateOptimized{
    template <class T, TZA_index_t r>
    class StateFullReadReverseWithDeleteBlockIterator{
        std::vector<TZA_index_t> block_type_to_count_map_;
        std::vector<std::vector<T*>>& index_blocks_list_;
        std::vector<TZA_index_t> powers_of_b_;
        TZA_index_t size_;
        TZA_index_t current_item_iterated_;
        TZA_index_t items_left_iterate_;
        TZA_index_t current_block_type_;
        TZA_index_t current_block_position_;
        TZA_index_t current_element_position_;

        void DeAllocate(T* block_pointer, [[maybe_unused]] TZA_index_t block_size){
            delete[] block_pointer;
        }
    public :

        explicit StateFullReadReverseWithDeleteBlockIterator(const std::vector<TZA_index_t>& block_type_to_count_map, std::vector<std::vector<T*>>& index_blocks_list,
                                              const std::vector<TZA_index_t>& powers_of_b, TZA_index_t size): block_type_to_count_map_(block_type_to_count_map), index_blocks_list_(index_blocks_list),
                                                                                                              powers_of_b_(powers_of_b), size_(size) {
            current_item_iterated_ = 0;
            items_left_iterate_ = size_;
            current_block_type_ = 0;
            powers_of_b_[0] = powers_of_b_ [1];

            if (size_ > 0) {
                while (block_type_to_count_map_[current_block_type_] == 0) {
                    ++current_block_type_;
                }

                if (current_block_type_ == 0) {
                    current_element_position_ = ((block_type_to_count_map_[current_block_type_] - 1) % powers_of_b_[1]);
                    if (block_type_to_count_map_[0] > powers_of_b_[1]) {
                        block_type_to_count_map_[0] = 2;
                    } else {
                        block_type_to_count_map_[0] = 1;
                    }
                    current_block_position_ = block_type_to_count_map_[0] - 1;
                } else {
                    current_block_position_ = block_type_to_count_map_[current_block_type_] - 1;
                    current_element_position_ = powers_of_b_[current_block_type_] - 1;
                }
            }
        }

        [[nodiscard]] bool HasNextItem() const{
            if(items_left_iterate_ > 0) return true;
            return false;
        }

        T GetNextItem() {
            if(items_left_iterate_ == 0){
                return T();
            }
            T item = index_blocks_list_[current_block_type_][current_block_position_][current_element_position_];
            ++current_item_iterated_;
            if(current_element_position_ == 0){
                if(current_block_position_ == 0){
                    DeAllocate(index_blocks_list_[current_block_type_][current_block_position_], powers_of_b_[current_block_type_]);
                    index_blocks_list_[current_block_type_].pop_back();
                    ++current_block_type_;
                    while (block_type_to_count_map_[current_block_type_] == 0) {
                        ++current_block_type_;
                    }
                    current_block_position_ = block_type_to_count_map_[current_block_type_] - 1;
                    current_element_position_ = powers_of_b_[current_block_type_] - 1;
                }
                else{
                    DeAllocate(index_blocks_list_[current_block_type_][current_block_position_], powers_of_b_[current_block_type_]);
                    index_blocks_list_[current_block_type_].pop_back();
                    current_element_position_ = powers_of_b_[current_block_type_] - 1;
                    --current_block_position_;
                }
            }
            else{
                --current_element_position_;
            }
            --items_left_iterate_;
            return item;
        }
    };


}



#endif //RESIZABLEARRAYIMPLEMENTATIONS_STATEFULLREADREVERSEWITHDELETEBLOCKITERATOR_H
