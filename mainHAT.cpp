

#include <iostream>

#include "HashedArrayTree/HashedArrayTree.h"


int main()
{
    HashedArrayTree<int, 16> hashedArrayTree;


    uint64_t  iterations = std::pow(2,20) + 1;

    auto start = std::chrono::high_resolution_clock ::now();

    for(int i = 0; i < iterations;++i){
        hashedArrayTree.PushBack(i);
    }

    auto stop = std::chrono::high_resolution_clock ::now();

    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"duration for hat ds in microseconds "<< duration.count() <<"\n";







//
//    uint64_t lastelem = hashedArrayTree.Locate(hashedArrayTree.GetSize() - 1);
//
//
//    std::cout<<"last elem  "<< lastelem <<"\n";
//
//    std::cout<<"HAT size : "<<hashedArrayTree.GetSize()<<"\n";
//
//
//
//    start = std::chrono::high_resolution_clock ::now();
//
//    for(int i = 0; i < hashedArrayTree.GetSize();++i){
//       int val =  hashedArrayTree.Locate(i);
//       if(val != i){
//           std::cout<<"error is val\n";
//       }
//    }
//
//    stop = std::chrono::high_resolution_clock ::now();
//
//    duration = duration_cast<std::chrono::milliseconds>(stop - start);
//
//    std::cout<<"duration for HAT Locate in milliseconds "<< duration.count() <<"\n";
//
//
//    start = std::chrono::high_resolution_clock ::now();
//
//    for(int i = 0; i < iterations;++i){
//        hashedArrayTree.PopBack();
//    }
//
//    stop = std::chrono::high_resolution_clock ::now();
//
//    duration = duration_cast<std::chrono::milliseconds>(stop - start);
//
//    std::cout<<"duration for HAT Pop in milliseconds "<< duration.count() <<"\n";
//
//    std::cout<<"HAT size : "<<hashedArrayTree.GetSize()<<"\n";



}

