//
// Created by Abhijith  K A on 07/04/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_TREEARRAYNODE_H
#define RESIZABLEARRAYIMPLEMENTATIONS_TREEARRAYNODE_H

#include "BaseTreeArrayNode.h"
#include <cmath>

namespace TreeArray {

    using tree_array_size_t = uint64_t;

    template <class T>
    class TreeArrayNode{
        tree_array_size_t sub_universe_size_;
        TreeArrayNode<T>** sub_universe_list_;

    public:
        explicit TreeArrayNode(tree_array_size_t sub_universe_size):sub_universe_size_(sub_universe_size){
            sub_universe_list_ = new TreeArrayNode<T>*[sub_universe_size_];
            TreeArrayNode<T>** current = sub_universe_list_;
            for(tree_array_size_t index = 0; index < sub_universe_size_;++index){
                *current = nullptr;
                ++current;
            }
        }
        T GetBaseNode(tree_array_size_t index) const{
           TreeArrayNode<T>* current_sub_universe =  sub_universe_list_[index/sub_universe_size_];
            if (sub_universe_size_ != base_universe_size) {
                if (current_sub_universe == nullptr) {
                    return T();
                }
                return current_sub_universe->GetBaseNode(index % sub_universe_size_);
            } else {
                if (current_sub_universe == nullptr) {
                    return T();
                }
                BaseTreeArrayNode<T>* base_node_casted = reinterpret_cast<BaseTreeArrayNode<T>*>(current_sub_universe);
                return base_node_casted->GetValue(index % sub_universe_size_);
            }
        }
        [[nodiscard]] tree_array_size_t GetSubUniverseSize() const{
            return sub_universe_size_;
        }

        void Insert(tree_array_size_t index, T item){
            TreeArrayNode<T>*  current_sub_universe =  sub_universe_list_[index/sub_universe_size_];
            if(sub_universe_size_ == base_universe_size){
                if(current_sub_universe == nullptr){
                    sub_universe_list_[index/sub_universe_size_] = reinterpret_cast<TreeArrayNode<T>*>(new BaseTreeArrayNode<T>());
                }
               (reinterpret_cast<BaseTreeArrayNode<T>*>(sub_universe_list_[index/sub_universe_size_]))->SetValue(index % sub_universe_size_, item);
                return;
            }
            if(current_sub_universe == nullptr){
                tree_array_size_t  sub_sub_universe_size = std::sqrt(sub_universe_size_);
                sub_universe_list_[index/sub_universe_size_] = new TreeArrayNode(sub_sub_universe_size);
            }
            sub_universe_list_[index/sub_universe_size_]->Insert(index%sub_universe_size_, item);
        }

        void DeleteAll(){
            TreeArrayNode<T>** current = sub_universe_list_;
            if(sub_universe_list_ != nullptr) {
                for (tree_array_size_t index = 0; index < sub_universe_size_; ++index) {
                    if (*current != nullptr) {
                        if (sub_universe_size_ == base_universe_size) {
                            delete reinterpret_cast<BaseTreeArrayNode<T> *>(*current);
                        } else {
                            (*current)->DeleteAll();
                        }
                    }
                    ++current;
                }
                delete[] sub_universe_list_;
            }
        }
    };



}

#endif //RESIZABLEARRAYIMPLEMENTATIONS_TREEARRAYNODE_H
