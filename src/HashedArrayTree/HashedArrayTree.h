//
// Created by Abhijith  K A on 23/03/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_HASHEDARRAYTREE_H
#define RESIZABLEARRAYIMPLEMENTATIONS_HASHEDARRAYTREE_H


#include <cmath>
#include <iterator>
#include <vector>
#include <iostream>


using hashed_array_index_t = std::size_t;
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
    hashed_array_index_t index_block_index_;
    T ** index_block_;

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
        T ** previous_index_block = index_block_;
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
        index_block_ = AllocateIndexBlock(current_block_size_);
        index_block_index_ = 0;
        n1_ = 0;
        n0_ = 0;

        hashed_array_index_t  active_old_n1 = 0;
        hashed_array_index_t  active_old_n0 = 0;

        hashed_array_index_t  items_left_to_copy = size_;
        while(items_left_to_copy > 0){
            if(n1_ == 0 || n0_ == current_block_size_){
                index_block_[index_block_index_] = AllocateBlock(current_block_size_);
                ++index_block_index_;
                ++n1_;
                n0_ = 0;
            }
            else{
                hashed_array_index_t elements_count = 0;
                while(elements_count < current_block_size_ && items_left_to_copy > 0){
                    if(active_old_n0 >= previous_block_size_copy){
                        DeallocateBlock(previous_index_block[active_old_n1], previous_block_size);
                        ++active_old_n1;
                        active_old_n0 = 0;
                        if(active_old_n1 == previous_block_size_copy - 1){
                            previous_block_size_copy = old_n0;
                        }
                    }

                    index_block_[index_block_index_ - 1][n0_] = std::move(previous_index_block[active_old_n1][active_old_n0]);
                    ++n0_;
                    ++elements_count;
                    ++active_old_n0;
                    --items_left_to_copy;
                }
            }
        }

        DeallocateBlock(previous_index_block[active_old_n1], previous_block_size);
        DeallocateBlock(previous_index_block, previous_block_size);

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
        T** previous_index_block = index_block_;
        hashed_array_index_t old_n1 = n1_;
        hashed_array_index_t old_n0 = n0_;

        current_block_size_ = current_block_size_ >> 1;
        --current_block_size_log_2_;
        max_current_block_size_capacity_ = max_current_block_size_capacity_ >> 2;
        min_current_block_size_capacity_ = max_current_block_size_capacity_ >> 4;
        if(min_current_block_size_capacity_ == 0){
            min_current_block_size_capacity_ = 1;
        }
        index_block_ = AllocateIndexBlock(current_block_size_);
        index_block_index_ = 0;
        n1_ = 0;
        n0_ = 0;

        hashed_array_index_t  active_old_n1 = 0;
        hashed_array_index_t  active_old_n0 = 0;

        hashed_array_index_t  items_left_to_copy = size_;
        while(items_left_to_copy > 0){
            if(n1_ == 0 || n0_ == current_block_size_){
                index_block_[index_block_index_] = AllocateBlock(current_block_size_);
                ++index_block_index_;
                ++n1_;
                n0_ = 0;
            }
            else{
                hashed_array_index_t elements_count = 0;
                while(elements_count < current_block_size_ && items_left_to_copy > 0){
                    if(active_old_n0 >= previous_block_size_copy){
                        DeallocateBlock(previous_index_block[active_old_n1], previous_block_size);
                        ++active_old_n1;
                        active_old_n0 = 0;
                        if(active_old_n1 == previous_block_size_copy - 1){
                            previous_block_size_copy = old_n0;
                        }
                    }
                    index_block_[index_block_index_ - 1][n0_] = std::move(previous_index_block[active_old_n1][active_old_n0]);
                    ++n0_;
                    ++elements_count;
                    ++active_old_n0;
                    --items_left_to_copy;
                }
            }
        }
        DeallocateBlock(previous_index_block[active_old_n1], previous_block_size);
        DeallocateBlock(previous_index_block, previous_block_size);
    }

    void DeallocateBlock(T* block_address, [[maybe_unused]] hashed_array_index_t block_size){
        for(hashed_array_index_t index = 0; index < block_size; ++index){
            block_address[index].~T();
        }
        delete [] block_address;

    }

    void DeallocateBlock(T** block_address, [[maybe_unused]] hashed_array_index_t block_size){
        delete [] block_address;

    }

    T* AllocateBlock(hashed_array_index_t block_size){
        return new T[block_size];
    }

    T** AllocateIndexBlock(hashed_array_index_t block_size){
        T** index_block = new T*[block_size];
        for(hashed_array_index_t index = 0; index < block_size; ++index){
            index_block[index] = nullptr;
        }
        return index_block;
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
        index_block_ = AllocateIndexBlock(current_block_size_);
        index_block_index_ = 0;
    }

    T& operator[](std::size_t index) {
        return Locate(index);
    }

    const T& operator[](std::size_t index) const {
        return Locate(index);
    }

    const T& Locate(hashed_array_index_t index) const {
        hashed_array_index_t  block_index = GetBlockIndex(index, current_block_size_, current_block_size_log_2_);
        hashed_array_index_t item_index = GetElementIndex(index, current_block_size_, current_block_size_log_2_);
        return index_block_[block_index][item_index];
    }

    T& Locate(hashed_array_index_t index)  {
        hashed_array_index_t  block_index = GetBlockIndex(index, current_block_size_, current_block_size_log_2_);
        hashed_array_index_t item_index = GetElementIndex(index, current_block_size_, current_block_size_log_2_);
        return index_block_[block_index][item_index];
    }

    void Insert(hashed_array_index_t index, T value){
        hashed_array_index_t  block_index = GetBlockIndex(index, current_block_size_, current_block_size_log_2_);
        hashed_array_index_t item_index = GetElementIndex(index, current_block_size_, current_block_size_log_2_);
        index_block_[block_index][item_index] = std::move(value);
    }

    void PushBack(const T& item) {
        if(size_ == max_current_block_size_capacity_){
            Grow();
        }
        if(n0_ == current_block_size_ || n1_ == 0){
            ++n1_;
            if(is_empty_block_present_){
                index_block_[index_block_index_] = empty_block_address;
                ++index_block_index_;
                is_empty_block_present_ = false;
            }
            else{
                index_block_[index_block_index_] = AllocateBlock(current_block_size_);
                ++index_block_index_;
            }

            n0_ = 0;
        }
        (index_block_[n1_ - 1])[n0_] = item;
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
            --index_block_index_;
            is_empty_block_present_ = true;
            --n1_;
        }

    }

    [[nodiscard]] hashed_array_index_t GetSize() const {
        return size_;
    }

    ~HashedArrayTree(){
        for(hashed_array_index_t index = 0; index < index_block_index_;++index){
            if(index_block_[index]) {
                DeallocateBlock(index_block_[index], current_block_size_);
            }
        }
        if(is_empty_block_present_){
            DeallocateBlock(empty_block_address, current_block_size_);
        }
        DeallocateBlock(index_block_, current_block_size_);
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
        iterator(HashedArrayTree<T, initial_block_size> *container, std::size_t index) : container_(container),
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
        HashedArrayTree<T, initial_block_size> *container_;
        std::size_t index_ = 0;
    };

    iterator begin(){
        return iterator(this, 0);
    }
    iterator end(){
       return  iterator(this, size_);
    }


};


#endif //RESIZABLEARRAYIMPLEMENTATIONS_HASHEDARRAYTREE_H
