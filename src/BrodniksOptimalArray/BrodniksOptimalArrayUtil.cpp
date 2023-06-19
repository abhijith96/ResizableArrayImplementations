//
// Created by Abhijith  K A on 24/03/23.
//

#include "BrodniksOptimalArrayUtil.h"

namespace BrodniksOptimalArray{

    bool IsSuperBlockIndexOdd(brodniks_array_size_t super_block_index) {
        return (super_block_index & 1) == 0;
    }

    brodniks_array_size_t GetCeilOfNDividedByTwo(brodniks_array_size_t n) {

        if (n & 1) {
            return (n >> 1) + 1;
        }
        return n >> 1;

    }

    brodniks_array_size_t GetFloorOfNDividedByTwo(brodniks_array_size_t n) {

        if (n & 1) {
            return (n >> 1);
        }
        return n >> 1;

    }

}