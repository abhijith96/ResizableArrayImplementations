//
// Created by Abhijith  K A on 30/03/23.
//


#include "TarjanAndZewicksOptimalArray/TarjanAndZewicksOptimalArray.h"
#include <iostream>
#include <chrono>

int main(){

    TarjanAndZewicksOptimalArray::TarjanAndZewicksOptimalArray<int, 3, 6> tarjanAndZewicksOptimalArray;

    const int iterations = std::pow(2,20);


    auto start = std::chrono::high_resolution_clock ::now();
    for(int i  = 0; i < iterations; ++i){
        tarjanAndZewicksOptimalArray.PushBack(i);
    }

    auto stop = std::chrono::high_resolution_clock ::now();

    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for tarjan push ds in milliseconds "<< duration.count() <<"\n";
    //tarjanAndZewicksOptimalArray.PushBack(iterations);

    start = std::chrono::high_resolution_clock ::now();

    for(int i  = 0; i < iterations; ++i){
        int val = tarjanAndZewicksOptimalArray.Locate(i);
        if(val != i){
            std::cout<<"error in ds\n";
        }
    }

    TarjanAndZewicksOptimalArray::TZA_index_t  size = tarjanAndZewicksOptimalArray.Size();
    std::cout<<"size is : "<<size<<"\n";

    stop = std::chrono::high_resolution_clock ::now();

    duration = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for tarjan locate ds in milliseconds "<< duration.count() <<"\n";

    start = std::chrono::high_resolution_clock ::now();

    for(int i  = 0; i < iterations; ++i){
        tarjanAndZewicksOptimalArray.PopBack();
    }

    stop = std::chrono::high_resolution_clock ::now();

    duration = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for tarjan pop ds in milliseconds "<< duration.count() <<"\n";

     size = tarjanAndZewicksOptimalArray.Size();
    std::cout<<"size is : "<<size<<"\n";


};