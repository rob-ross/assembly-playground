//  Ch04_07.cpp
//
//  Created by Rob Ross on 9/18/26.
//



#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "MT.h"

// Ch04_07_fasm.asm, Ch04_07_fasm.s
extern "C" int ReverseArrayI32_a(int32_t* y, const int32_t* x, int32_t n);

// Ch04_07_misc.cpp
void InitArrays(int32_t* y, int32_t* x, int32_t n);
void DisplayResults(const int32_t* y, const int32_t* x, int32_t n, int rc);


void InitArrays(int32_t* y, int32_t* x, int32_t n)
{
    constexpr int max_val = 1000;
    constexpr int min_val = -max_val;
    constexpr unsigned int rng_seed = 17;

    MT::FillArray(x, n, min_val, max_val, rng_seed, true);
    memset(y, 0, sizeof(int32_t) * n);
}

void DisplayResults(const int32_t* y, const int32_t* x, int32_t n, int rc)
{
    if (rc != 0)
    {
        std::cout << "\n----- Results for Ch04_07 -----\n";

        constexpr int w = 5;

        for (int i = 0; i < n; i++)
        {
            std::cout << "  i: " << std::setw(w) << i;
            std::cout << "  y: " << std::setw(w) << y[i];
            std::cout << "  x: " << std::setw(w) << x[i] << '\n';

            if (x[i] != y[n - 1 - i])
            {
                std::cout << "ReverseArrayI32_a() element compare error\n";
                break;
            }
        }
    }
    else
        std::cout << "ReverseArrayI32_a() failed\n";
}


int main()
{
    constexpr int32_t n = 25;
    int32_t y[n], x[n];

    InitArrays(y, x, n);

    int rc = ReverseArrayI32_a(y, x, n);
    DisplayResults(y, x, n, rc);
    return 0;
}
