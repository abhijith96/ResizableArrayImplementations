//
// Created by Abhijith  K A on 30/03/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_CONSTANTS_H
#define RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_CONSTANTS_H

#include <cstdint>

namespace TarjanAndZewicksOptimalArray{

    using TZA_index_t = uint64_t;

    //back of buggy first rebuild

//    [[maybe_unused]] void Rebuild(double growth_factor){
//
//        //rebuild such that all blocks except last block should be full. use size variable.
//        TZA_index_t new_base_block_size = static_cast<TZA_index_t>(current_base_block_size_ * growth_factor);
//        TZA_index_t new_base_block_size_power_r = std::pow(new_base_block_size, r);
//        TZA_index_t current_new_block_type_size = new_base_block_size_power_r / new_base_block_size;
//        TZA_index_t current_new_block_type_index = r - 1;
//        TZA_index_t current_new_block_type_block_count = 1;
//        TZA_index_t current_new_block_type_block_element_count = 0;
//
//        TZA_index_t current_old_block_type_size = current_base_block_size_power_r_;
//
//        TZA_index_t elements_left_to_copy = size_;
//
//        std::vector<T*> new_block_index_list_for_current_new_block_type;
//        while(current_new_block_type_size > elements_left_to_copy && current_new_block_type_index > 1){
//            current_new_block_type_size /= new_base_block_size;
//            --current_new_block_type_index;
//        }
//        new_block_index_list_for_current_new_block_type.reserve(2*  new_base_block_size);
//        T* active_new_block_start_address = Allocate(current_new_block_type_size);
//        new_block_index_list_for_current_new_block_type.push_back(active_new_block_start_address);
//
//        std::vector<TZA_index_t> new_block_type_to_count_map(r, 0);
//
//        std::vector<std::vector<T*>> new_index_block_list(r);
//
//
//        for(TZA_index_t block_type_index = r - 1; block_type_index >=1; -- block_type_index){
//            current_old_block_type_size /= current_base_block_size_;
//            TZA_index_t current_old_block_type_count = block_type_to_count_map_.at(block_type_index);
//            for(TZA_index_t current_old_block_position = 0; current_old_block_position < current_old_block_type_count; ++current_old_block_position){
//                T* current_old_block = index_blocks_list_.at(block_type_index).at(current_old_block_position);
//                for(TZA_index_t element_index = 0; element_index < current_old_block_type_size;++element_index) {
//                    bool did_block_type_change = false;
//                    TZA_index_t current_new_block_type_index_copy = current_new_block_type_index;
//                    TZA_index_t current_new_block_type_size_copy = current_new_block_type_size;
//                    if (current_new_block_type_block_element_count == current_new_block_type_size) {
//                        while (current_new_block_type_size > elements_left_to_copy &&
//                               current_new_block_type_index > 1) {
//                            current_new_block_type_size /= new_base_block_size;
//                            --current_new_block_type_index;
//                            did_block_type_change = true;
//                        }
//                    }
//                    if(did_block_type_change){
//                        new_index_block_list.at(current_new_block_type_index_copy) = std::move(new_block_index_list_for_current_new_block_type);
//                        new_block_type_to_count_map.at(current_new_block_type_index_copy) = current_new_block_type_block_count;
//                        new_block_index_list_for_current_new_block_type = std::vector<T*>{};
//                        new_block_index_list_for_current_new_block_type.reserve(2* new_base_block_size);
//                        current_new_block_type_block_count = 0;
//                        current_new_block_type_block_element_count = 0;
//                        active_new_block_start_address = Allocate(current_new_block_type_size);
//                        new_block_index_list_for_current_new_block_type.push_back(active_new_block_start_address);
//                    }
//
//                    if(!(block_type_index == 1 && current_old_block_position == current_old_block_type_count - 1 &&
//                         element_index >= block_type_to_count_map_.at(0))){
//                        T old_item = current_old_block[element_index];
//                        if(current_new_block_type_block_count == 2 * new_base_block_size && current_new_block_type_block_element_count == current_new_block_type_size){
//                            new_index_block_list.at(current_new_block_type_index) = std::move(new_block_index_list_for_current_new_block_type);
//                            new_block_index_list_for_current_new_block_type = std::vector<T*>{};
//                            new_block_index_list_for_current_new_block_type.reserve(2* new_base_block_size);
//                            --current_new_block_type_index;
//                            new_block_type_to_count_map.at(block_type_index) = current_new_block_type_block_count;
//                            current_new_block_type_block_count = 0;
//                            current_new_block_type_block_element_count = 0;
//                            current_new_block_type_size /= new_base_block_size;
//                            active_new_block_start_address = Allocate(current_new_block_type_size);
//                            new_block_index_list_for_current_new_block_type.push_back(active_new_block_start_address);
//
//                        }
//                        if(current_new_block_type_block_count < 2*new_base_block_size && current_new_block_type_block_element_count == current_new_block_type_size){
//                            ++current_new_block_type_block_count;
//                            active_new_block_start_address = Allocate(current_new_block_type_size);
//                            new_block_index_list_for_current_new_block_type.push_back(active_new_block_start_address);
//                            current_new_block_type_block_element_count = 0;
//                        }
//                        active_new_block_start_address[current_new_block_type_block_element_count] = old_item;
//                        ++current_new_block_type_block_element_count;
//                        --elements_left_to_copy;
//                    }
//                    else{
//                        break;
//                    }
//                }
//                DeAllocate(current_old_block, current_old_block_type_size);
//            }
//        }
//        new_index_block_list.at(current_new_block_type_index) = std::move(new_block_index_list_for_current_new_block_type);
//        if(current_new_block_type_block_element_count > 0 && current_new_block_type_block_element_count < current_new_block_type_size){
//            ++current_new_block_type_block_count;
//        }
//        new_block_type_to_count_map.at(current_new_block_type_index) = current_new_block_type_block_count;
//        if(current_new_block_type_index == 1){
//            new_block_type_to_count_map.at(0) = current_new_block_type_block_element_count;
//        }
//        block_type_to_count_map_ = std::move(new_block_type_to_count_map);
//        current_base_block_size_ = new_base_block_size;
//        current_base_block_size_power_r_ = new_base_block_size_power_r;
//        current_base_block_size_division_four_power_r_ = std::pow(static_cast<TZA_index_t>(new_base_block_size/4), r);
//        index_blocks_list_ = std::move(new_index_block_list);
//        if(block_type_to_count_map_.at(1) == 0){
//            index_blocks_list_.at(1).push_back(Allocate(new_base_block_size));
//            block_type_to_count_map_.at(1) = 1;
//            block_type_to_count_map_.at(0) = 0;
//        }
//    }


}

#endif //RESIZABLEARRAYIMPLEMENTATIONS_TARJANANDZEWICKSOPTIMALARRAY_CONSTANTS_H
