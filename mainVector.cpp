//
// Created by Abhijith  K A on 01/04/23.
//

#include <vector>
#include <chrono>
#include <cmath>
#include <iostream>

int main(){

   std::vector<int> vector;


    uint64_t  iterations = std::pow(2,30.5) + 1;

    auto start = std::chrono::high_resolution_clock ::now();

    for(int i = 0; i < iterations;++i){
        vector.push_back(i);
    }

    auto stop = std::chrono::high_resolution_clock ::now();

    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"duration for vector ds in microseconds "<< duration.count() <<"\n";




//    uint64_t lastelem = vector.at(vector.size() - 1);
//
//
//    std::cout<<"last elem vector "<< lastelem <<"\n";
//
//
//
//
//
//    start = std::chrono::high_resolution_clock ::now();
//
//    for(int i = 0; i < vector.size(); ++i){
//        vector.at(i);
//    }
//
//    stop = std::chrono::high_resolution_clock ::now();
//
//    duration = duration_cast<std::chrono::milliseconds>(stop - start);
//
//    std::cout<<"duration for vector Locate in milliseconds "<< duration.count() <<"\n";
}