//  Ch08_06.cpp
//
//  Created by Rob Ross on 10/14/26.
//

#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cstdint>
#include "MT.h"
#include "AlignedMem.h"


// Ch08_06_fasm.asm, Ch08_06_fasm.s
extern "C" bool CalcMeanU8_avx(double* mean_x, uint64_t* sum_x, const uint8_t* x,
    uint32_t n);

// Ch08_06_fcpp.cpp
extern bool CalcMeanU8_cpp(double* mean_x, uint64_t* sum_x, const uint8_t* x,
    uint32_t n);

// Ch08_06_misc.cpp
extern void InitArray(uint8_t* x, uint32_t n, unsigned int seed);

// Miscellaneous constants
constexpr size_t c_Alignment = 16;
constexpr uint32_t c_NumElements = 16384;
constexpr unsigned int c_RngSeedVal = 29;


bool CalcMeanU8_cpp(double* mean_x, uint64_t* sum_x, const uint8_t* x,
    uint32_t n)
{
    // Validate arguments
    if (n <= 0 || (n % 64) != 0)
        return false;

    if (!AlignedMem::IsAligned(x, c_Alignment))
        return false;

    // Calculate pixel mean
    uint64_t sum_x_temp = 0;

    for (size_t i = 0; i < n; i++)
        sum_x_temp += x[i];

    *sum_x = sum_x_temp;
    *mean_x = (double)sum_x_temp / n;
    return true;
}


void InitArray(uint8_t* x, uint32_t n, unsigned int rng_seed)
{
    constexpr int rng_min_val = 0;
    constexpr int rng_max_val = 255;
    MT::FillArray(x, n, rng_min_val, rng_max_val, rng_seed);
}


static void CalcMeanU8()
{
    constexpr char nl = '\n';
    constexpr uint32_t n = c_NumElements;

    AlignedArray<uint8_t> x_aa(n, c_Alignment);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    bool rc0, rc1;
    uint64_t sum_x0, sum_x1;
    double mean_x0, mean_x1;

    rc0 = CalcMeanU8_cpp(&mean_x0, &sum_x0, x, n);
    rc1 = CalcMeanU8_avx(&mean_x1, &sum_x1, x, n);

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "\nCalcMeanU8_cpp() results:\n";
    std::cout << "rc0:     " << rc0 << nl;
    std::cout << "sum_x0:  " << sum_x0 << nl;
    std::cout << "mean_x0: " << mean_x0 << nl;

    std::cout << "\nCalcMeanU8_avx() results:\n";
    std::cout << "rc1:     " << rc1 << nl;
    std::cout << "sum_x1:  " << sum_x1 << nl;
    std::cout << "mean_x1: " << mean_x1 << nl;
}

int main()
{
    std::cout << "----- Results for Ch08_06 -----\n";

    CalcMeanU8();
    return 0;
}
