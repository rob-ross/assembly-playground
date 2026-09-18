//  Ch04_01.cpp
//
//  Created by Rob Ross on 9/17/26.
//
#include <cstddef>
#include <cstdint>
#include <iostream>
#include "MT.h"


// Ch04_01_fasm.asm, Ch04_01_fasm.s
extern "C" int64_t SumElementsI32_a(const int32_t* x, size_t n);

// Ch04_01_fcpp.cpp
extern int64_t SumElementsI32_cpp(const int32_t* x, size_t n);

// Ch04_01_misc.cpp
extern void FillArray(int32_t* x, size_t n);
extern void DisplayResults(const int32_t* x, size_t n, int64_t sum1, int64_t sum2);

int64_t SumElementsI32_cpp(const int32_t* x, size_t n)
{
    int64_t sum = 0;

    for (size_t i = 0; i < n; i++)
        sum += x[i];

    return sum;
}


void FillArray(int32_t* x, size_t n)
{
    constexpr int max_val = 1000;
    constexpr int min_val = -max_val;
    constexpr unsigned int rng_seed = 1337;

    MT::FillArray(x, n, min_val, max_val, rng_seed, true);
}

void DisplayResults(const int32_t* x, size_t n, int64_t sum1, int64_t sum2)
{
    constexpr char nl = '\n';

    std::cout << "----- Results for Ch04_01 -----\n";

    for (size_t i = 0; i < n; i++)
        std::cout << "x[" << i << "] = " << x[i] << nl;
    std::cout << nl;

    std::cout << "sum1 = " << sum1 << nl;
    std::cout << "sum2 = " << sum2 << nl;
}


int main()
{
    constexpr size_t n = 20;
    int32_t x[n];

    FillArray(x, n);

    int64_t sum1 = SumElementsI32_cpp(x, n);
    int64_t sum2 = SumElementsI32_a(x, n);

    DisplayResults(x, n, sum1, sum2);
    return 0;
}
