//
// Created by Abhijith  K A on 24/03/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_BRODNIKSOPTIMALARRAY_H
#define RESIZABLEARRAYIMPLEMENTATIONS_BRODNIKSOPTIMALARRAY_H

#include <vector>
#include <cmath>
#include <iostream>
//#include "BrodniksOptimalArray.h"


namespace BrodniksOptimalArray{

    using brodniks_array_size_t = uint64_t;

    bool IsSuperBlockIndexOdd(brodniks_array_size_t super_block_index) {
        return (super_block_index & 1);
        //return super_block_index % 2 == 1;
    }

    brodniks_array_size_t GetCeilOfNDividedByTwo(brodniks_array_size_t n) {

        if (n & 1) {
            return (n >> 1) + 1;
        }
        return n >> 1;

    }

    brodniks_array_size_t GetFloorOfNDividedByTwo(brodniks_array_size_t n) {

        if (n & 1) {
            return (n >> 1);
        }
        return n >> 1;

    }



    std::pair<brodniks_array_size_t , brodniks_array_size_t> GetMSBAndTwoPowerMSB(brodniks_array_size_t number){
        brodniks_array_size_t  v = number;
        brodniks_array_size_t r = 0;
        brodniks_array_size_t power_of_r = 1;

        while (v >>= 1) {
            r++;
            power_of_r *= 2;
        }
        return {r + 1, power_of_r * 2};
    }

    brodniks_array_size_t GetNumberOfDataBlocksBeforeCurrentSuperBlock(brodniks_array_size_t super_block_index){
        brodniks_array_size_t floor_of_super_block_index_by_two = GetFloorOfNDividedByTwo(super_block_index);
        brodniks_array_size_t ceil_of_super_block_index_by_two = GetCeilOfNDividedByTwo(super_block_index);
        return (1 << floor_of_super_block_index_by_two) +  (1 << ceil_of_super_block_index_by_two) - 2;

    }

    brodniks_array_size_t GetMSB(brodniks_array_size_t number) {

       // #ifdef HAS_MSB
            int msb = 63 - __builtin_clzll(number);
            return msb + 1;
       //#else
//            brodniks_array_size_t  v = number;
//            brodniks_array_size_t r = 0;
//
//            while (v >>= 1) {
//            r++;
//
//            }
//            return r + 1;
       // #endif

//        int msb = 63 - __builtin_clzll(number);
//        return msb + 1;
    }


    template <class T>

    class BrodniksOptimalArray{
    private:
        std::vector<T*> index_block_;
        std::vector<brodniks_array_size_t> super_block_index_to_number_of_data_blocks_preceding_it_map_;

        brodniks_array_size_t size_;
        brodniks_array_size_t no_of_elements_in_last_data_block_;
        brodniks_array_size_t no_of_data_blocks_in_last_super_block_;
        brodniks_array_size_t last_data_block_index_;
        brodniks_array_size_t last_super_block_index_;
        brodniks_array_size_t last_super_block_size_;
        brodniks_array_size_t last_data_block_size_;
        bool is_empty_data_block_present_;

        T* Allocate(brodniks_array_size_t required_block_size){
            return new T[required_block_size];
        }

        void DeAllocate(T* block, brodniks_array_size_t block_size){
           delete[] block;
        }



    public:

        explicit BrodniksOptimalArray(): size_(0), no_of_elements_in_last_data_block_(0), no_of_data_blocks_in_last_super_block_(1), last_data_block_index_(0), last_super_block_index_(0), last_super_block_size_(1),
                                         last_data_block_size_(1){
            index_block_.resize(1);
            index_block_.at(0) = Allocate(1);
            is_empty_data_block_present_ = false;
            super_block_index_to_number_of_data_blocks_preceding_it_map_.reserve(64);
            super_block_index_to_number_of_data_blocks_preceding_it_map_.push_back(0);
        }

        const T& Locate(brodniks_array_size_t index){
            if(index >= size_){
               return T();
            }
            brodniks_array_size_t k_plus_1 = 0;
            k_plus_1 = GetMSB(index + 1);
            brodniks_array_size_t super_block_index = k_plus_1 - 1;
            brodniks_array_size_t one = 1;
            brodniks_array_size_t elements_bit_count = GetCeilOfNDividedByTwo(super_block_index);
            brodniks_array_size_t data_block_bit_count = GetFloorOfNDividedByTwo(super_block_index);
            brodniks_array_size_t r = index + 1;
            brodniks_array_size_t elem_index = r & ((one << elements_bit_count) - 1);
            brodniks_array_size_t data_block_index = (r  >> elements_bit_count) & ((one << data_block_bit_count) - 1);

            brodniks_array_size_t no_of_data_blocks_in_preceding_super_blocks = super_block_index_to_number_of_data_blocks_preceding_it_map_.at(super_block_index);
            //brodniks_array_size_t  no_of_data_blocks_in_preceding_super_blocks = GetNumberOfDataBlocksBeforeCurrentSuperBlock(super_block_index);

            return index_block_.at(no_of_data_blocks_in_preceding_super_blocks + data_block_index)[elem_index];
        }

        void PushBack(const T& element){

          if(no_of_elements_in_last_data_block_ == last_data_block_size_) {
              if (no_of_data_blocks_in_last_super_block_ == last_super_block_size_) {
                  ++last_super_block_index_;
                  super_block_index_to_number_of_data_blocks_preceding_it_map_.push_back(
                          super_block_index_to_number_of_data_blocks_preceding_it_map_.back() + (last_super_block_size_)
                  );
                  if (!IsSuperBlockIndexOdd(last_super_block_index_)) {
                      last_super_block_size_ *= 2;
                  } else {
                      last_data_block_size_ *= 2;
                  }
                  no_of_data_blocks_in_last_super_block_ = 0;
              }

              if (!is_empty_data_block_present_) {
                T *data_block = Allocate(last_data_block_size_);
                index_block_.push_back(data_block);
              }
              else{
                  is_empty_data_block_present_ = false;
              }
              ++last_data_block_index_;
              no_of_elements_in_last_data_block_ = 0;
              ++no_of_data_blocks_in_last_super_block_;
          }

          index_block_[last_data_block_index_][no_of_elements_in_last_data_block_] = element;
          ++no_of_elements_in_last_data_block_;
          ++size_;

      }

        void PopBack() {

            if (size_ == 0) {
                return;
            }
            --size_;
            --no_of_elements_in_last_data_block_;

            if (no_of_elements_in_last_data_block_ == 0) {
                if (is_empty_data_block_present_) {
                    // pass correct size for empty data block
                    brodniks_array_size_t  size_of_empty_block = last_data_block_size_;
                    if(no_of_data_blocks_in_last_super_block_ == last_super_block_size_){
                        if(!IsSuperBlockIndexOdd(last_super_block_index_)){
                            size_of_empty_block = 2* last_data_block_size_;
                        }
                    }
                    DeAllocate(index_block_[last_data_block_index_ + 1], size_of_empty_block);
                    index_block_.pop_back();
                }
                is_empty_data_block_present_ = true;
                --last_data_block_index_;
                --no_of_data_blocks_in_last_super_block_;
                if (no_of_data_blocks_in_last_super_block_ == 0) {
                    --last_super_block_index_;
                    if (IsSuperBlockIndexOdd(last_super_block_index_)){
                        last_super_block_size_ /= 2;
                    } else {
                        last_data_block_size_ /= 2;
                    }
                    no_of_data_blocks_in_last_super_block_ = last_super_block_size_;
                }
                no_of_elements_in_last_data_block_ = last_data_block_size_;
            }
        }

        [[nodiscard]] brodniks_array_size_t Size() {
            return size_;
        }

        ~BrodniksOptimalArray(){
            brodniks_array_size_t  super_block_index = 0;
            brodniks_array_size_t current_super_block_size = 1;
            brodniks_array_size_t current_data_block_size = 1;
            brodniks_array_size_t current_data_block_in_super_block = 0;
            for(T* block : index_block_){
                DeAllocate(block, current_data_block_size);
                ++current_data_block_in_super_block;
                if(current_data_block_in_super_block == current_super_block_size){
                    ++super_block_index;
                    if(IsSuperBlockIndexOdd(super_block_index)){
                        current_data_block_size *= 2;
                    }
                    else{
                        current_super_block_size *= 2;
                    }
                    current_data_block_in_super_block = 0;
                }
            }
        }
    };


}


#endif //RESIZABLEARRAYIMPLEMENTATIONS_BRODNIKSOPTIMALARRAY_H
