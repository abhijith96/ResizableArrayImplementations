//
// Created by Abhijith  K A on 12/04/23.
//



#include "TarjansArrayRGrows/TarjanAndZewicksOptimalArrayRGrows.h"
#include <chrono>
#include <vector>
#include <iostream>


int main(){

    int iterations = std::pow(2,30)  + 1;

    TarjanAndZewicksOptimalArrayRGrows::TarjanAndZewicksOptimalArray<int, 4, 2> tarjanAndZewicksOptimalArray;

    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < iterations; ++i){
        tarjanAndZewicksOptimalArray.PushBack(i);
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration_push_back = duration_cast<std::chrono::milliseconds>(stop - start);


    start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < iterations; ++i){
        int val = tarjanAndZewicksOptimalArray.LocateNew(i);
        if(val != i){
            std::cout<<"error in val\n";
        }
    }


     stop = std::chrono::high_resolution_clock::now();

    auto duration_locate = duration_cast<std::chrono::milliseconds>(stop - start);


    start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < iterations; ++i){
        tarjanAndZewicksOptimalArray.PopBack();
    }

    stop = std::chrono::high_resolution_clock::now();

    auto duration_pop_back = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "duration for tarjan pushback in  iteration in milliseconds " << duration_push_back.count() << "\n";
    std::cout << "duration for tarjan locate in  iteration in milliseconds " << duration_locate.count() << "\n";
    std::cout << "duration for tarjan pop back in  iteration in milliseconds " << duration_pop_back.count() << "\n";

    std::cout<<" current R value : "<<tarjanAndZewicksOptimalArray.GetCurrentRValue()<<"\n";

    return 0;
}