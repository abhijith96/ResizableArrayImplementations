

#include <iostream>

#include "HashedArrayTree/HashedArrayTree.h"
#include <random>


int main()
{

    HashedArrayTree<int, 16> hashedArrayTree;


    uint64_t  iterations = std::pow(2,20) + 1;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> rand_dist(0,  static_cast<int>(iterations));

    auto start = std::chrono::high_resolution_clock ::now();

    for(int i = 0; i < iterations;++i){
        int random_value = rand_dist(gen);
        hashedArrayTree.PushBack(random_value);
    }

    auto stop = std::chrono::high_resolution_clock ::now();

    auto duration_push_back = duration_cast<std::chrono::milliseconds>(stop - start);













    int sum = 0;


   start = std::chrono::high_resolution_clock ::now();

    for(int i = 0; i < hashedArrayTree.GetSize();++i){
       int val =  hashedArrayTree.Locate(i);
       if(val == i){
           ++sum;
       }
    }

    stop = std::chrono::high_resolution_clock ::now();



   auto duration_locate = duration_cast<std::chrono::milliseconds>(stop - start);








//
//    stop = std::chrono::high_resolution_clock ::now();
//
//    duration = duration_cast<std::chrono::milliseconds>(stop - start);
//
//    std::cout<<"duration for HAT Pop in milliseconds "<< duration.count() <<"\n";
//
//    std::cout<<"HAT size : "<<hashedArrayTree.GetSize()<<"\n";



//    start = std::chrono::high_resolution_clock ::now();
//
//
//
//
//    std::sort(hashedArrayTree.begin(), hashedArrayTree.end());
//
//    stop = std::chrono::high_resolution_clock ::now();
//
//    auto duration_sort = duration_cast<std::chrono::milliseconds>(stop - start);

    start = std::chrono::high_resolution_clock ::now();


    std::make_heap(hashedArrayTree.begin(), hashedArrayTree.end());

    std::sort_heap(hashedArrayTree.begin(), hashedArrayTree.end());

    stop = std::chrono::high_resolution_clock ::now();

    auto duration_sort = duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout<<"duration for hat  pushback ds in  milliseconds "<< duration_push_back.count() <<"\n";

    std::cout<<"duration for HAT locate in milliseconds "<< duration_locate.count() <<"\n";

    std::cout<<"duration for HAT heap sort in milliseconds "<< duration_sort.count() <<"\n";

    std::cout<<"size is  "<<hashedArrayTree.GetSize()<<"\n";

    std::cout<<"sum is   "<<sum<<"\n";

    std::cout<<"first val after sorting : "<<hashedArrayTree[0]<<"\n";

    std::cout<<"last after sorting : "<<hashedArrayTree[hashedArrayTree.GetSize() - 1]<<"\n";




}

