//  Ch08_05.cpp
//
//  Created by Rob Ross on 10/14/26.
//


#include <cstddef>
#include <cstdint>
#include <iostream>


#include "AlignedMem.h"
#include "MT.h"



// Ch08_05_fasm.asm, Ch08_05_fasm.s
extern "C" bool CalcMinMaxU8_avx(uint8_t* x_min, uint8_t* x_max,
    const uint8_t* x, size_t n);

// Ch08_05_fcpp.cpp
extern bool CalcMinMaxU8_cpp(uint8_t* x_min, uint8_t* x_max,
    const uint8_t* x, size_t n);

// Ch08_05_misc.cpp
extern void InitArray(uint8_t* x, size_t n, unsigned int rng_seed);

// c_NumElements must be > 0 and even multiple of 16
constexpr size_t c_NumElements = 10'000'000;
constexpr unsigned int c_RngSeedVal = 23;



bool CalcMinMaxU8_cpp(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n)
{
    // Validate argument value n
    if (n == 0 || (n % 16) != 0)
        return false;

    // Make sure array x is properly aligned
    if (!AlignedMem::IsAligned(x, 16))
        return false;

    // Find pixel minimum and maximum
    uint8_t min_val = 0xff;
    uint8_t max_val = 0;

    for (size_t i = 0; i < n; i++)
    {
        uint8_t val = *x++;

        if (val < min_val)
            min_val = val;
        else if (val > max_val)
            max_val = val;
    }

    *x_min = min_val;
    *x_max = max_val;
    return true;
}


void InitArray(uint8_t* x, size_t n, unsigned int rng_seed)
{
    int rng_min_val = 5;
    int rng_max_val = 250;
    MT::FillArray(x, n, rng_min_val, rng_max_val, rng_seed);

    // Use known min & max values for validation purposes
    x[(n / 4) * 3 + 1] = 2;
    x[n / 4 + 11] = 3;
    x[n / 2] = 252;
    x[n / 2 + 13] = 253;
    x[n / 8 + 5] = 4;
    x[n / 8 + 7] = 254;
}

#include "roblib/dev_utils.h"

static void CalcMinMaxU8()
{
    constexpr char nl = '\n';
    constexpr size_t n = c_NumElements;

    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    uint8_t x_min1 = 0, x_max1 = 0;
    uint8_t x_min2 = 0, x_max2 = 0;


    bool rc0;
    bool rc1;

    TIMEIT(rc0 = CalcMinMaxU8_cpp(&x_min1, &x_max1, x, n));
    TIMEIT(rc1 = CalcMinMaxU8_avx(&x_min2, &x_max2, x, n));

    /*

        rc0 = CalcMinMaxU8_cpp(&x_min1, &x_max1, x, n)  time: 0.020041 s, rc1 = CalcMinMaxU8_avx(&x_min2, &x_max2, x, n)  time: 0.000574 s,
        rc0 = CalcMinMaxU8_cpp(&x_min1, &x_max1, x, n)  time: 0.020172 s, rc1 = CalcMinMaxU8_avx(&x_min2, &x_max2, x, n)  time: 0.000535 s,
        rc0 = CalcMinMaxU8_cpp(&x_min1, &x_max1, x, n)  time: 0.020229 s, rc1 = CalcMinMaxU8_avx(&x_min2, &x_max2, x, n)  time: 0.000685 s,

     */

    std::cout << "\nCalcMinMaxU8_cpp() results:\n";
    std::cout << "rc0: " << rc0 << "  x_min1: " << (int)x_min1;
    std::cout << "  x_max1: " << (int)x_max1 << nl;

    std::cout << "\nCalcMinMaxU8_avx() results:\n";
    std::cout << "rc1: " << rc1 << "  x_min2: " << (int)x_min2;
    std::cout << "  x_max2: " << (int)x_max2 << nl;
}

int main()
{
    std::cout << "----- Results for Ch08_05 -----\n";

    CalcMinMaxU8();
    return 0;
}

