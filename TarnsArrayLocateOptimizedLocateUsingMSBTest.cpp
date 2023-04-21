//
// Created by Abhijith  K A on 11/04/23.
//
//
// Created by Abhijith  K A on 10/04/23.
//

#include "TarjanAndZewicksOptimalArrayLocateOptimized/TarjanAndZewicksOptimalArrayLocateOptimized.h"
#include <iostream>
#include <cmath>

int main() {
    TarjanAndZewicksOptimalArrayLocateOptimized::TarjanAndZewicksOptimalArray<int, 2, 4> tarjanAndZewicksOptimalArray;

//    for (int i = 0; i < 1000; ++i) {
//        tarjanAndZewicksOptimalArray.PushBack(i);
//    }
//
//    for (int i = 0; i < 50; ++i) {
//        tarjanAndZewicksOptimalArray.PopBack();
//    }
//
//    for (int i = 0; i < 500; ++i) {
//        tarjanAndZewicksOptimalArray.PushBack(i);
//    }
//
//    for (int i = 0; i < 1440; ++i) {
//        tarjanAndZewicksOptimalArray.PopBack();
//    }
//
//    for (int i = 0; i < 1000; ++i) {
//        tarjanAndZewicksOptimalArray.PushBack(i);
//    }
//
//    int size = tarjanAndZewicksOptimalArray.Size();
//    for (int i = 0; i < size; ++i) {
//        tarjanAndZewicksOptimalArray.PopBack();
//    }




    const int iterations = std::pow(2,10.5) + 1;

    auto start = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < iterations; ++i) {
        tarjanAndZewicksOptimalArray.PushBack(i);
    }
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration_push_back =  duration_cast<std::chrono::milliseconds>(stop - start);

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        int val = tarjanAndZewicksOptimalArray.Locate(i);
        if(val != i){
            std::cout<<"error in val\n";
        }
    }

    stop = std::chrono::high_resolution_clock::now();

    auto duration_locate = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "duration for tarjan pushback in  iteration in milliseconds " << duration_push_back.count() << "\n";

    std::cout << "duration for tarjan locate in  iteration in milliseconds " << duration_locate.count() << "\n";



}