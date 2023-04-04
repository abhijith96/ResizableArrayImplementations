//
// Created by Abhijith  K A on 23/03/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_HASHEDARRAYTREE_H
#define RESIZABLEARRAYIMPLEMENTATIONS_HASHEDARRAYTREE_H

#include <vector>
#include <cmath>


using hashed_array_index_t = uint64_t;
hashed_array_index_t constexpr default_block_size = 4;




template<class T, hashed_array_index_t initial_block_size = default_block_size>

class HashedArrayTree {
    hashed_array_index_t  max_capacity_ = std::numeric_limits<hashed_array_index_t>::max();
    hashed_array_index_t size_;
    hashed_array_index_t current_block_size_;
    hashed_array_index_t current_block_size_log_2_;
    hashed_array_index_t max_current_block_size_capacity_;
    hashed_array_index_t min_current_block_size_capacity_;
    bool is_empty_block_present_;
    T* empty_block_address;
    hashed_array_index_t n1_;
    hashed_array_index_t n0_;
    std::vector<T*> index_block_;

private:

    [[nodiscard]] hashed_array_index_t GetBlockIndex(hashed_array_index_t  index, [[maybe_unused]] hashed_array_index_t block_size, hashed_array_index_t block_size_log_2) const {
        return index >> block_size_log_2;
    }

    [[nodiscard]] hashed_array_index_t GetElementIndex(hashed_array_index_t index, hashed_array_index_t block_size,
                                                       [[maybe_unused]] hashed_array_index_t block_size_log_2) const{
        return index & (block_size - 1);
    }

    void Grow(){
        hashed_array_index_t  previous_block_size = current_block_size_;
        hashed_array_index_t  previous_block_size_copy = current_block_size_;
        std::vector<T*> previous_index_block = index_block_;
        hashed_array_index_t old_n1 = n1_;
        hashed_array_index_t old_n0 = n0_;

        if(is_empty_block_present_) {
            DeallocateBlock(empty_block_address, previous_block_size);
            is_empty_block_present_ = false;
        }

        current_block_size_ = current_block_size_ << 1;
        ++current_block_size_log_2_;
        max_current_block_size_capacity_ = max_current_block_size_capacity_ << 2;
        min_current_block_size_capacity_ = max_current_block_size_capacity_ >> 4;
        index_block_ = std::vector<T*>{};
        index_block_.reserve(current_block_size_);
        n1_ = 0;
        n0_ = 0;

        hashed_array_index_t  active_old_n1 = 0;
        hashed_array_index_t  active_old_n0 = 0;

        hashed_array_index_t  items_left_to_copy = size_;
        while(items_left_to_copy > 0){
            if(n1_ == 0 || n0_ == current_block_size_){
                index_block_.push_back(AllocateBlock(current_block_size_));
                ++n1_;
                n0_ = 0;
            }
            else{
                hashed_array_index_t elements_count = 0;
                while(elements_count < current_block_size_ && items_left_to_copy > 0){
                    if(active_old_n0 >= previous_block_size_copy){
                        DeallocateBlock(previous_index_block[active_old_n1], current_block_size_);
                        ++active_old_n1;
                        active_old_n0 = 0;
                        if(active_old_n1 == previous_block_size_copy - 1){
                            previous_block_size_copy = old_n0;
                        }
                    }
//                    std::copy(previous_index_block.at(active_old_n1) + active_old_n0, )
                    index_block_.back()[n0_] = std::move(previous_index_block[active_old_n1][active_old_n0]);
                    ++n0_;
                    ++elements_count;
                    ++active_old_n0;
                    --items_left_to_copy;
                }
            }
        }

        DeallocateBlock(previous_index_block.at(active_old_n1), previous_block_size);

    }

    void Shrink(){
        if(current_block_size_ <= initial_block_size){
            return;
        }

        if(is_empty_block_present_) {
            DeallocateBlock(empty_block_address, current_block_size_);
            is_empty_block_present_ = false;
        }
        hashed_array_index_t  previous_block_size = current_block_size_;
        hashed_array_index_t  previous_block_size_copy = current_block_size_;
        std::vector<T*> previous_index_block = index_block_;
        hashed_array_index_t old_n1 = n1_;
        hashed_array_index_t old_n0 = n0_;

        current_block_size_ = current_block_size_ >> 1;
        --current_block_size_log_2_;
        max_current_block_size_capacity_ = max_current_block_size_capacity_ >> 2;
        min_current_block_size_capacity_ = max_current_block_size_capacity_ >> 4;
        if(min_current_block_size_capacity_ == 0){
            min_current_block_size_capacity_ = 1;
        }
        index_block_ = std::vector<T*>{};
        index_block_.reserve(current_block_size_);
        n1_ = 0;
        n0_ = 0;

        hashed_array_index_t  active_old_n1 = 0;
        hashed_array_index_t  active_old_n0 = 0;

        hashed_array_index_t  items_left_to_copy = size_;
        while(items_left_to_copy > 0){
            if(n1_ == 0 || n0_ == current_block_size_){
                index_block_.push_back(AllocateBlock(current_block_size_));
                ++n1_;
                n0_ = 0;
            }
            else{
                hashed_array_index_t elements_count = 0;
                while(elements_count < current_block_size_ && items_left_to_copy > 0){
                    if(active_old_n0 >= previous_block_size_copy){
                        DeallocateBlock(previous_index_block.at(active_old_n1), previous_block_size);
                        ++active_old_n1;
                        active_old_n0 = 0;
                        if(active_old_n1 == previous_block_size_copy - 1){
                            previous_block_size_copy = old_n0;
                        }
                    }
//                    std::copy(previous_index_block.at(active_old_n1) + active_old_n0, )
                    index_block_.back()[n0_] = std::move(previous_index_block[active_old_n1][active_old_n0]);
                    ++n0_;
                    ++elements_count;
                    ++active_old_n0;
                    --items_left_to_copy;
                }
            }
        }
        DeallocateBlock(previous_index_block[active_old_n1], previous_block_size);
    }

    void DeallocateBlock(T* block_address, hashed_array_index_t block_size){
        delete [] block_address;

    }
    T* AllocateBlock(hashed_array_index_t block_size){
        return new T[block_size];
    }


public:

    explicit HashedArrayTree(): size_(0), current_block_size_(initial_block_size), max_current_block_size_capacity_(current_block_size_ * current_block_size_), index_block_(){
        min_current_block_size_capacity_ =  max_current_block_size_capacity_/16;
        if(current_block_size_ < 2){
           current_block_size_ = 2;
        }
        if(min_current_block_size_capacity_ == 0){
            min_current_block_size_capacity_ = 1;
        }
        is_empty_block_present_ = false;
        empty_block_address = nullptr;
        current_block_size_log_2_ = log2(current_block_size_);
        n0_ = 0;
        n1_ = 0;
        index_block_.reserve(initial_block_size);
    }

    const T& Locate(hashed_array_index_t index) const {
        if(index >= size_){
            throw std::invalid_argument("Array out of bound");
        }
        hashed_array_index_t  block_index = GetBlockIndex(index, current_block_size_, current_block_size_log_2_);
        hashed_array_index_t item_index = GetElementIndex(index, current_block_size_, current_block_size_log_2_);
        return index_block_[block_index][item_index];
    }

    void PushBack(const T& item) {
        if(size_ == max_current_block_size_capacity_){
            Grow();
        }
        if(n0_ == current_block_size_ || n1_ == 0){
            ++n1_;
            if(is_empty_block_present_){
                index_block_.push_back(empty_block_address);
                is_empty_block_present_ = false;
            }
            else{
                index_block_.push_back(AllocateBlock(current_block_size_));
            }

            n0_ = 0;
        }
        index_block_[n1_ - 1][n0_] = item;
        ++n0_;
        ++size_;

    }

    void PopBack() {
        if(size_ == 0){
            return;
        }
        if(size_ < min_current_block_size_capacity_){
            Shrink();
        }
        if(n0_ == 0 && n1_ > 0 ){
            n0_ = current_block_size_;
        }
        --n0_;
        --size_;
        if(n0_ == 0){
            n0_ = current_block_size_;
            if(is_empty_block_present_){
                DeallocateBlock(empty_block_address, current_block_size_);
            }
            empty_block_address = index_block_[n1_ - 1];
            index_block_.pop_back();
            is_empty_block_present_ = true;
            --n1_;
        }

    }

    [[nodiscard]] hashed_array_index_t GetSize() const {
        return size_;
    }

    ~HashedArrayTree(){
        for(T* block : index_block_){
            DeallocateBlock(block, current_block_size_);
        }
        if(is_empty_block_present_){
            DeallocateBlock(empty_block_address, current_block_size_);
        }
    }


};


#endif //RESIZABLEARRAYIMPLEMENTATIONS_HASHEDARRAYTREE_H
