//
// Created by Abhijith  K A on 01/04/23.
//

#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
#include "TreeArray/TreeArray.h"
#include <iostream>
#include<unistd.h>
#include <random>
#include "HashedArrayTree/HashedArrayTree.h"
#include "BrodniksOptimalArray/BrodniksOptimalArray.h"
#include "TarjanAndZewicksOptimalArray/TarjanAndZewicksOptimalArray.h"
int main(){




    std::vector<int> vector;
    HashedArrayTree<int, 16> hashedArrayTree;
    BrodniksOptimalArray::BrodniksOptimalArray<int> brodniksOptimalArray;
    TarjanAndZewicksOptimalArray::TarjanAndZewicksOptimalArray<int, 3, 4> tarjanAndZewicksOptimalArray;
    TarjanAndZewicksOptimalArray::TarjanAndZewicksOptimalArray<int, 3, 4> tarjanAndZewicksOptimalArray_r_4;


    uint64_t  iterations = std::pow(2,20) + 1;


    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> rand_dist(0,  static_cast<int>(iterations));

    auto  start = std::chrono::high_resolution_clock ::now();
    for(int i = 0; i < iterations;++i){
        int val = rand_dist(gen);
        vector.push_back(val);

    }
    auto  stop = std::chrono::high_resolution_clock ::now();
    auto duration_push_back = duration_cast<std::chrono::milliseconds>(stop - start);

   start = std::chrono::high_resolution_clock ::now();

    int sum = 0;
    for(int i = 0; i < iterations;++i){
        int val = vector[i];
       if(val == i){
           ++sum;
       }
    }

    stop = std::chrono::high_resolution_clock ::now();

    auto duration_sequential_access = duration_cast<std::chrono
            ::milliseconds>(stop - start);

    start = std::chrono::high_resolution_clock ::now();
    std::make_heap(vector.begin(), vector.end());
    std::sort_heap(vector.begin(), vector.end());
    stop = std::chrono::high_resolution_clock ::now();
    auto duration_sort = duration_cast<std::chrono::milliseconds>(stop - start);

//    start = std::chrono::high_resolution_clock ::now();
//    std::sort(vector.begin(), vector.end());
//    stop = std::chrono::high_resolution_clock ::now();
//    auto duration_sort = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for vector pushback in milliseconds  "<< duration_push_back.count() <<"\n";
    std::cout<<"duration for vector locate  in milliseconds  "<< duration_sequential_access.count() <<"\n";
    std::cout<<"vector size "<< vector.size()<<"\n";

    std::cout<<"sum is  "<< sum<<"\n";

    //std::cout << "duration for vector std::sort  in milliseconds  " << duration_sort.count() << "\n";

    std::cout << "duration for vector make heap and heap sort  in milliseconds  " << duration_sort.count() << "\n";












}