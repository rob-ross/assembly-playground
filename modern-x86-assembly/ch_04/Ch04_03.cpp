//  Ch04_3.cpp
//
//  Created by Rob Ross on 9/17/26.
//

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>

// Ch04_03_fasm.asm, Ch04_03_fasm.s
extern "C" void CalcMat2dSquares_a(int32_t* y, const int32_t* x, size_t m,
    size_t n);

// Ch04_03_fcpp.cpp
extern void CalcMat2dSquares_cpp(int32_t* y, const int32_t* x, size_t m,
    size_t n);

// Ch04_03_misc.cpp
extern void DisplayResults(const int32_t* y1, const int32_t* y2, const int32_t* x,
    size_t m, size_t n);


void DisplayResults(const int32_t* y1, const int32_t* y2, const int32_t* x,
    size_t m, size_t n)
{
    std::cout << "----- Results for Ch04_03 -----\n";

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            size_t kx = j * m + i;
            size_t ky = i * n + j;

            std::cout << "x[" << std::setw(2) << j << "][" << std::setw(2) << i << "] = ";
            std::cout << std::setw(6) << x[kx] << "   ";

            std::cout << "y1[" << std::setw(2) << i << "][" << std::setw(2) << j << "] = ";
            std::cout << std::setw(6) << y1[ky] << "   ";

            std::cout << "y2[" << std::setw(2) << i << "][" << std::setw(2) << j << "] = ";
            std::cout << std::setw(6) << y2[ky] << '\n';

            if (y1[ky] != y2[ky])
            {
                std::cout << "\nmatrix element compare failed\n";
                break;
            }
        }
    }
}

void CalcMat2dSquares_cpp(int32_t* y, const int32_t* x, size_t m, size_t n)
{
    // Calculate y[i][i] = x[j][i] * x[j][i]

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            size_t kx = j * m + i;
            size_t ky = i * n + j;

            y[ky] = x[kx] * x[kx];
        }
    }
}

int main()
{
    constexpr size_t m = 6;
    constexpr size_t n = 3;
    constexpr int32_t x[n][m]
    {
        { 1, 2, 3, 4, 5, 6 },
        { 7, 8, 9, 10, 11, 12 },
        { 13, 14, 15, 16, 17, 18 }
    };

    int32_t y1[m][n], y2[m][n];

    CalcMat2dSquares_cpp(&y1[0][0], &x[0][0], m, n);
    CalcMat2dSquares_a(&y2[0][0], &x[0][0], m, n);

    DisplayResults(&y1[0][0], &y2[0][0], &x[0][0], m, n);
    return 0;
}
