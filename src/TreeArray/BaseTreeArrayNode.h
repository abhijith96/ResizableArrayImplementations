//
// Created by Abhijith  K A on 07/04/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_BASETREEARRAYNODOE_H
#define RESIZABLEARRAYIMPLEMENTATIONS_BASETREEARRAYNODOE_H

#include <vector>

namespace TreeArray{
    using tree_array_size_t = uint64_t;
    constexpr tree_array_size_t base_universe_size = 16;

    template <class T>
    class BaseTreeArrayNode{
        std::vector<T> base_list_;
    public:
        explicit BaseTreeArrayNode(){
            base_list_.resize(base_universe_size);
        }
        const T& GetValue(tree_array_size_t index) const{
            return base_list_.at(index);
        }
        void SetValue(tree_array_size_t index, T item){
            base_list_.at(index) = std::move(item);
        }
    };
}

#endif //RESIZABLEARRAYIMPLEMENTATIONS_BASETREEARRAYNODOE_H
