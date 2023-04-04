//
// Created by Abhijith  K A on 29/03/23.
//

#ifndef RESIZABLEARRAYIMPLEMENTATIONS_BRODNIKSOPTIMALARRAYUTIL_H
#define RESIZABLEARRAYIMPLEMENTATIONS_BRODNIKSOPTIMALARRAYUTIL_H

#include <cstdint>

namespace BrodniksOptimalArray {

    using brodniks_array_size_t = uint64_t;

    bool IsSuperBlockIndexOdd(brodniks_array_size_t super_block_index);


    brodniks_array_size_t GetCeilOfNDividedByTwo(brodniks_array_size_t n);

    brodniks_array_size_t GetFloorOfNDividedByTwo(brodniks_array_size_t n);

}

#endif //RESIZABLEARRAYIMPLEMENTATIONS_BRODNIKSOPTIMALARRAYUTIL_H
