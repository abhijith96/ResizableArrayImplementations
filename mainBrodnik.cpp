//
// Created by Abhijith  K A on 24/03/23.
//


#include "BrodniksOptimalArray/BrodniksOptimalArray.h"

int main(){




    BrodniksOptimalArray::BrodniksOptimalArray<int> brodniksOptimalArray;

    std::cout<< sizeof(int)<<" size of int \n";

    uint64_t  iterations = std::pow(2,20);







    auto start = std::chrono::high_resolution_clock ::now();

    for(int i = 0; i < iterations;++i){
        brodniksOptimalArray.PushBack(i);
    }

    auto stop = std::chrono::high_resolution_clock ::now();

    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for insertion in brodnik ds in milliseconds "<< duration.count() <<"\n";




    uint64_t lastelem = brodniksOptimalArray.Locate(brodniksOptimalArray.Size() - 1);


    std::cout<<"last elem brodnik  "<< lastelem<<"\n";






    start = std::chrono::high_resolution_clock ::now();
    for (int i = 0; i < brodniksOptimalArray.Size(); ++i) {
       int val =  brodniksOptimalArray.Locate(i);
       if(val != i){
           std::cout<<"value is : " <<val<<"\n";
           std::cout<<"error in ds\n";
       }
    }
    stop = std::chrono::high_resolution_clock ::now();

    duration = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for brodnik Locate in milliseconds "<< duration.count() <<"\n";


    start = std::chrono::high_resolution_clock ::now();
    int k = 0;
    while (k < 10) {
        brodniksOptimalArray.PopBack();
        brodniksOptimalArray.PopBack();
        brodniksOptimalArray.PushBack(30);
        brodniksOptimalArray.PushBack(31);

        ++k;
    }




    start = std::chrono::high_resolution_clock ::now();
    for (int i = 0; i < brodniksOptimalArray.Size(); ++i) {
        int val =  brodniksOptimalArray.Locate(i);
        if(val != i){
            std::cout<<"value is : " <<val<<"\n";
            std::cout<<"error in ds\n";
        }
    }
    stop = std::chrono::high_resolution_clock ::now();

    duration = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for brodnik Locate again in milliseconds "<< duration.count() <<"\n";

    start = std::chrono::high_resolution_clock ::now();
    for (int i = 0; i < iterations; ++i) {
        brodniksOptimalArray.PopBack();
    }
    stop = std::chrono::high_resolution_clock ::now();

    duration = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for pop  last back "<< duration.count() <<"\n";


    uint64_t size = brodniksOptimalArray.Size();


    std::cout<<"size :   "<< size<<"\n";



}