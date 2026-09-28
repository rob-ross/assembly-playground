//  Ch05_07.cpp
//
//  Created by Rob Ross on 9/27/26.
//


#include <cstddef>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include "MT.h"

// Ch05_07_fasm.asm, Ch05_07_fasm.s
extern "C" bool CalcMeanF64_avx(double* mean, const double* x, size_t n);
extern "C" bool CalcStDevF64_avx(double* st_dev, const double* x, size_t n,
    double mean);

// Ch05_07_fcpp.cpp
extern bool CalcMeanF64_cpp(double* mean, const double* x, size_t n);
extern bool CalcStDevF64_cpp(double* st_dev, const double* x, size_t n,
    double mean);

// Ch05_07_misc.cpp
extern void InitArray(double* x, size_t n);

// Miscellaneous constants
constexpr size_t c_NumElements = 91;
constexpr double c_RngMin = 1.0;
constexpr double c_RngMax = 100.0;
constexpr unsigned int c_RngSeed = 13;


void InitArray(double* x, size_t n)
{
    MT::FillArrayFP(x, n, c_RngMin, c_RngMax, c_RngSeed);
}


bool CalcMeanF64_cpp(double* mean, const double* x, size_t n)
{
    if (n < 2)
        return false;

    double sum = 0.0;

    for (size_t i = 0; i < n; i++)
        sum += x[i];

    *mean = sum / static_cast<double>(n);
    return true;
}

bool CalcStDevF64_cpp(double* st_dev, const double* x, size_t n, double mean)
{
    if (n < 2)
        return false;

    double sum_squares = 0.0;

    for (size_t i = 0; i < n; i++)
    {
        double temp = x[i] - mean;
        sum_squares += temp * temp;
    }

    *st_dev = sqrt(sum_squares / ( static_cast<double>(n) - 1.0));
    return true;
}


static void CalcMeanStDevF64()
{
    constexpr size_t n = c_NumElements;
    std::vector<double> x_v(n);
    double* x = x_v.data();

    InitArray(x, n);

    double mean1, mean2, st_dev1, st_dev2;

    bool rc1 = CalcMeanF64_cpp(&mean1, x, n);
    bool rc2 = CalcMeanF64_avx(&mean2, x, n);
    bool rc3 = CalcStDevF64_cpp(&st_dev1, x, n, mean1);
    bool rc4 = CalcStDevF64_avx(&st_dev2, x, n, mean2);

    std::cout << "----- Results for Ch05_07 -----\n";
    std::cout << std::fixed << std::setprecision(6);

    if (rc1 && rc2 && rc3 && rc4)
    {
        constexpr int w = 10;
        constexpr char nl = '\n';

        std::cout << "n:       " << std::setw(w) << n << nl;
        std::cout << "mean1:   " << std::setw(w) << mean1 << "  ";
        std::cout << "st_dev1: " << std::setw(w) << st_dev1 << nl;
        std::cout << "mean2:   " << std::setw(w) << mean2 << "  ";
        std::cout << "st_dev2: " << std::setw(w) << st_dev2 << nl;
    }
    else
        std::cout << "Invalid return code\n";
}

int main()
{
    CalcMeanStDevF64();
    return 0;
}
