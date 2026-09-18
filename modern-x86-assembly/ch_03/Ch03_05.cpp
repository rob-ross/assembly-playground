//  Ch03_05.cpp
//
//  Created by Rob Ross on 9/17/26.

#include <cstdint>
#include <iostream>
#include <iomanip>

// Ch03_05_fasm.asm, Ch03_05_fasm.s
extern "C" bool CalcSumCubes_a(int64_t* sum, int64_t n);

// Ch03_05_fcpp.cpp
extern bool CalcSumCubes_cpp(int64_t* sum, int64_t n);

// Ch03_05_misc.cpp
extern void DisplayResults(int id, int64_t n, int64_t sum1, bool rc1,
    int64_t sum2, bool rc2);

// Ch03_05.cpp
extern "C" int64_t g_ValMax;



constexpr int64_t c_ValMax = 77935;
int64_t g_ValMax = c_ValMax;


void DisplayResults(int id, int64_t n, int64_t sum1, bool rc1,
    int64_t sum2, bool rc2)
{
    constexpr char nl = '\n';
    const char* err_msg = "error: 'n' is out of range";

    std::cout << nl << "----- Test case #" << id << " -----\n";
    std::cout << "n = " << n << nl;

    std::cout << "sum1 = ";

    if (rc1)
        std::cout << sum1 << nl;
    else
        std::cout << err_msg << nl;

    std::cout << "sum2 = ";

    if (rc2)
        std::cout << sum2 << nl;
    else
        std::cout << err_msg << nl;

    if (sum1 != sum2)
        std::cout << "Compare test failed!\n";
}

bool CalcSumCubes_cpp(int64_t* sum, int64_t  n)
{
    if (n <= 0 || n > g_ValMax)
    {
        *sum = 0;
        return false;
    }

    int64_t temp1 = n * (n + 1) / 2;

    *sum = temp1 * temp1;
    return true;
}


int main()
{
    constexpr int64_t n_vals[] { 3, 4, 21, 0,
        c_ValMax, c_ValMax + 1, 100, -42, };

    constexpr int64_t num_n_vals = sizeof(n_vals) / sizeof(int64_t);

    std::cout << "----- Results for Ch03_05 -----\n";

    for (int i = 0; i < num_n_vals; i++)
    {
        int64_t sum1, sum2;
        int64_t n = n_vals[i];

        bool rc1 = CalcSumCubes_cpp(&sum1, n);
        bool rc2 = CalcSumCubes_a(&sum2, n);

        DisplayResults(i, n, sum1, rc1, sum2, rc2);
    }

    return 0;
}

/*
 * 
 *
 */
