//
// Created by Abhijith  K A on 10/04/23.
//

#include "TarjanAndZewicksOptimalArrayLocateOptimized/TarjanAndZewicksOptimalArrayLocateOptimized.h"
#include <iostream>
#include <cmath>
#include <random>

int main() {
    TarjanAndZewicksOptimalArrayLocateOptimized::TarjanAndZewicksOptimalArray<int, 8, 4> tarjanAndZewicksOptimalArray;

    const int iterations = std::pow(2,26) + 500;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> rand_dist(0,  static_cast<int>(iterations));

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        int val = rand_dist(gen);
        tarjanAndZewicksOptimalArray.PushBack(val);
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration_pushback = duration_cast<std::chrono::milliseconds>(stop - start);






    int iter = 1;

    int sum = 0;

    auto stateful_read_iterator = tarjanAndZewicksOptimalArray.GetStateFullReadIterator();
    int k = 0;

//    start = std::chrono::high_resolution_clock::now();
//    while(stateful_read_iterator.HasNextItem()){
//        int val = stateful_read_iterator.GetNextItem();
//        if(val != k){
//            std::cout<<"error in iteration\n";
//        }
//        //sum += val;
//    }
//
//    stop = std::chrono::high_resolution_clock::now();
//
//    auto duration6 = duration_cast<std::chrono::milliseconds>(stop - start);
//
//    std::cout << "duration for tarjan locate in  iterattor in milliseconds " << duration6.count() << "\n";

//    auto stateful_read_reverse_iterator = tarjanAndZewicksOptimalArray.GetStateFullReadReverseIterator();
//    k = tarjanAndZewicksOptimalArray.Size() - 1;
//
//    start = std::chrono::high_resolution_clock::now();
//    while(stateful_read_reverse_iterator.HasNextItem()){
//        int val = stateful_read_reverse_iterator.GetNextItem();
//        if(val != k){
//            std::cout<<"error in iteration\n";
//        }
//        --k;
//        //sum += val;
//    }
//
//    stop = std::chrono::high_resolution_clock::now();

//    auto duration3 = duration_cast<std::chrono::milliseconds>(stop - start);
//
//    std::cout << "duration for tarjan locate in reverse iteration in milliseconds " << duration3.count() << "\n";
//    std::cout << "sum : " << sum << "\n";
//    std::cout << "size : " << tarjanAndZewicksOptimalArray.Size() << "\n";


    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        int val = tarjanAndZewicksOptimalArray.LocateNew(i);
       if(val != i){
          ++sum;
       }
    }


    stop = std::chrono::high_resolution_clock::now();


    auto duration_locate = duration_cast<std::chrono::milliseconds>(stop - start);




//    start = std::chrono::high_resolution_clock::now();
//    std::sort(tarjanAndZewicksOptimalArray.begin(), tarjanAndZewicksOptimalArray.end());
//
//    stop = std::chrono::high_resolution_clock::now();
//
//    auto duration_sort = duration_cast<std::chrono::milliseconds>(stop - start);

    start = std::chrono::high_resolution_clock::now();
    std::make_heap(tarjanAndZewicksOptimalArray.begin(), tarjanAndZewicksOptimalArray.end());
    std::sort_heap(tarjanAndZewicksOptimalArray.begin(), tarjanAndZewicksOptimalArray.end());

    stop = std::chrono::high_resolution_clock::now();

    auto duration_heap_sort = duration_cast<std::chrono::milliseconds>(stop - start);


    std::cout << "duration for tarjan Pushback ds in milliseconds " << duration_pushback.count() << "\n";

    std::cout << "duration for tarjan locate ds in milliseconds " << duration_locate.count() << "\n";



    std::cout << "duration for tarjan std::heap sort ds in milliseconds " << duration_heap_sort.count() << "\n";

    std::cout << "sum : " << sum << "\n";
    std::cout << "size : " << tarjanAndZewicksOptimalArray.Size() << "\n";

    std::cout << "last elem " << tarjanAndZewicksOptimalArray[tarjanAndZewicksOptimalArray.Size() - 1] << "\n";

    std::cout << "first elem " << tarjanAndZewicksOptimalArray[0] << "\n";


    return 0;
}