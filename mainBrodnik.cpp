//
// Created by Abhijith  K A on 24/03/23.
//

#include <random>
#include "BrodniksOptimalArray/BrodniksOptimalArray.h"

int main(){




    BrodniksOptimalArray::BrodniksOptimalArray<int> brodniksOptimalArray;



    uint64_t  iterations = std::pow(2,26) + 1;







    int sum = 0;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> rand_dist(0,  static_cast<int>(iterations));

    auto start = std::chrono::high_resolution_clock ::now();


    for(int i = 0; i < iterations;++i){
         int val = rand_dist(gen);
        brodniksOptimalArray.PushBack(val);
    }

    auto stop = std::chrono::high_resolution_clock ::now();

    auto duration_push_back = duration_cast<std::chrono::milliseconds>(stop - start);

   // std::cout<<"duration for insertion in brodnik ds in microseconds "<< duration.count() <<"\n";

    start = std::chrono::high_resolution_clock ::now();


    for(int i = 0; i < iterations;++i){
      int val =  brodniksOptimalArray.Locate(i);
      if(i == val){
          ++sum;
      }
    }

    stop = std::chrono::high_resolution_clock ::now();

    auto duration_locate = duration_cast<std::chrono::milliseconds>(stop - start);






//    uint64_t lastelem = brodniksOptimalArray.Locate(brodniksOptimalArray.Size() - 1);
//
//
//    std::cout<<"last elem brodnik  "<< lastelem<<"\n";
//
//
//
//
//
//




//

//start = std::chrono::high_resolution_clock ::now();
//
//    std::sort(brodniksOptimalArray.begin(), brodniksOptimalArray.end());
//
//    stop = std::chrono::high_resolution_clock ::now();
//
//
//    auto duration_std_sort = duration_cast<std::chrono::milliseconds>(stop - start);

    start = std::chrono::high_resolution_clock ::now();

    std::make_heap(brodniksOptimalArray.begin(), brodniksOptimalArray.end());
    std::sort_heap(brodniksOptimalArray.begin(), brodniksOptimalArray.end());

    stop = std::chrono::high_resolution_clock ::now();


    auto duration_std_heap_sort = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for brodnik ds pushback  milliseconds "<< duration_push_back.count() <<"\n";
    std::cout<<"duration for brodnik ds  locate milliseconds "<< duration_locate.count() <<"\n";

    std::cout<<"brodnik size "<< brodniksOptimalArray.Size() <<"\n";

    std::cout<<"brodnik first elem  "<< brodniksOptimalArray[0] <<"\n";

    std::cout<<"brodnik lst elem  "<< brodniksOptimalArray[brodniksOptimalArray.Size() - 1] <<"\n";

    std::cout<<"sum  "<< sum <<"\n";

    std::cout<<"duration for brodnik ds std::heapsort milliseconds "<< duration_std_heap_sort.count() <<"\n";


}