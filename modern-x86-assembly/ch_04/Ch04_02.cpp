//  Ch04_02.cpp
//
//  Created by Rob Ross on 9/17/26.
//


#include <cstddef>
#include <cstdint>

#include <iostream>
#include <iomanip>
#include <cstring>
#include "MT.h"


// Ch04_02_fasm.asm, Ch04_02_fasm.s
extern "C" void CalcArrayVals_a(int64_t* c, const int64_t* a, const int64_t* b,
    size_t n);

// Ch04_02_fcpp.cpp
extern void CalcArrayVals_cpp(int64_t* c, const int64_t* a, const int64_t* b,
    size_t n);

// Ch04_02_misc.cpp
extern void FillArrays(int64_t* c1, int64_t* c2, int64_t* a, int64_t* b, size_t n);

extern void DisplayResults(const int64_t* c1, const int64_t* c2, const int64_t* a,
    const int64_t* b, size_t n);


void CalcArrayVals_cpp(int64_t* c, const int64_t* a, const int64_t* b, size_t n)
{
    for (size_t i = 0; i < n; i++)
        c[i] = (a[i] * 25) / (b[i] + 10);
}


void FillArrays(int64_t* c1, int64_t* c2, int64_t* a, int64_t* b, size_t n)
{
    constexpr int max_val = 1000;
    constexpr int min_val = -max_val;
    constexpr unsigned int rng_seed = 1001;

    MT::FillArray(a, n, min_val, max_val, rng_seed, true);
    MT::FillArray(b, n, min_val, max_val, rng_seed / 7, true);

    memset(c1, 0, sizeof(int64_t) * n);
    memset(c2, 0, sizeof(int64_t) * n);
}

void DisplayResults(const int64_t* c1, const int64_t* c2, const int64_t* a,
    const int64_t* b, size_t n)
{
    std::cout << "----- Results for Ch04_02 -----\n";

    for (size_t i = 0; i < n; i++)
    {
        std::cout << "a[" << std::setw(2) << i << "]: " << std::setw(8) << a[i];
        std::cout << "  ";
        std::cout << "b[" << std::setw(2) << i << "]: " << std::setw(8) << b[i];
        std::cout << "  ";
        std::cout << "c1[" << std::setw(2) << i << "]: " << std::setw(8) << c1[i];
        std::cout << "  ";
        std::cout << "c2[" << std::setw(2) << i << "]: " << std::setw(8) << c2[i];
        std::cout << '\n';

        if (c1[i] != c2[i])
        {
            std::cout << "array element compare failed\n";
            break;
        }
    }
}


int main()
{
    constexpr size_t n = 20;
    int64_t a[n], b[n], c1[n], c2[n];

    FillArrays(c1, c2, a, b, n);

    CalcArrayVals_cpp(c1, a, b, n);
    CalcArrayVals_a(c2, a, b, n);

    DisplayResults(c1, c2, a, b, n);
    return 0;
}
