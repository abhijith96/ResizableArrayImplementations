//
// Created by Abhijith  K A on 07/04/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_TREEARRAY_H
#define RESIZABLEARRAYIMPLEMENTATIONS_TREEARRAY_H

#include <vector>
#include "TreeArrayNode.h"
#include "BaseTreeArrayNode.h"

namespace TreeArray{

    using tree_array_size_t = uint64_t;
    template <class T>
    class TreeArray{
        tree_array_size_t universe_size_;
        TreeArrayNode<T>* root_node_;

    public:
        explicit TreeArray(tree_array_size_t universe_size_):universe_size_(universe_size_),
        root_node_(nullptr){
        }
        T Locate(tree_array_size_t index){
            if(root_node_){
                return root_node_->GetBaseNode(index);
            }
            return T();
        }
        void Insert(tree_array_size_t  index, T item){
            if(root_node_ == nullptr){
                tree_array_size_t sub_universe_size = std::sqrt(universe_size_);
                root_node_ = new TreeArrayNode<T>(sub_universe_size);
            }
            root_node_->Insert(index, item);
        }

        void DeleteAll(){
            if(root_node_ != nullptr) {
                root_node_->DeleteAll();
                delete root_node_;
            }
        }
        ~TreeArray(){
            DeleteAll();
        }
    };

}

#endif //RESIZABLEARRAYIMPLEMENTATIONS_TREEARRAY_H
