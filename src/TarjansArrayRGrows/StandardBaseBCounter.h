//
// Created by Abhijith  K A on 10/04/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_STANDARDBASEBCOUNTER_H
#define RESIZABLEARRAYIMPLEMENTATIONS_STANDARDBASEBCOUNTER_H

#include "Constants.h"
#include <vector>

namespace TarjanAndZewicksOptimalArrayRGrows{

    class StandardBaseBCounter{
        TZA_index_t base_;
        TZA_index_t number_of_digits_;
        std::vector<TZA_index_t>counter_;


    public:

        explicit StandardBaseBCounter(TZA_index_t base,TZA_index_t number_of_digits) : base_(base), number_of_digits_(number_of_digits),
        counter_(number_of_digits, 0){
        }


        void Increment(){
            TZA_index_t digit = 0;
            while(digit < number_of_digits_){
                ++counter_.at(digit);
                if(counter_.at(digit) == base_){
                    counter_.at(digit) = 0;
                    ++digit;
                }
                else{
                    break;
                }
            }
        }

        void Decrement(){
            TZA_index_t digit = 0;
            while(digit < number_of_digits_){
                if(counter_.at(digit) > 0){
                    --counter_.at(digit);
                    break;
                }
                else{
                    counter_.at(digit) = base_ - 1;
                    ++digit;
                }
            }
        }
    };

}

#endif //RESIZABLEARRAYIMPLEMENTATIONS_STANDARDBASEBCOUNTER_H
