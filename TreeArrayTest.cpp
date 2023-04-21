//
// Created by Abhijith  K A on 07/04/23.
//

#include "TreeArray/TreeArray.h"
#include <cmath>
#include <iostream>

int main(){

    TreeArray::tree_array_size_t capacity = std::pow(2,32);
    TreeArray::TreeArray<int> treeArray{capacity};

    TreeArray::tree_array_size_t iterations =  std::pow(2,30.5);

    for(TreeArray::tree_array_size_t index = 0; index < iterations;++index){
        treeArray.Insert(index, index);
    }
    for(TreeArray::tree_array_size_t index = 0; index < iterations;++index){
       int val =  treeArray.Locate(index);
       if(val != index){
           break;
           std::cout<<"error\n";
       }
    }


    return 0;
};