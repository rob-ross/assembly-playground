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

/*
 *
 *
 x[row][col] , x[n][m], x[3][6]
     x[0] ==   {  1,  2,  3,  4,  5,  6 },
     x[1] ==   {  7,  8,  9, 10, 11, 12 },
     x[2] ==   { 13, 14, 15, 16, 17, 18 }

  y[row][col], y[m][n], y[6][3]
      y[0] ==  { 0, 0, 0 },
      y[1] ==  { 0, 0, 0 },
      y[2] ==  { 0, 0, 0 },
      y[3] ==  { 0, 0, 0 },
      y[4] ==  { 0, 0, 0 },
      y[5] ==  { 0, 0, 0 },

m = 6, n = 3
1. Outer start
    i == 0; i < 6
2.  Inner start
    j == 0; j < 3
    kx := 0 * 6 + 0 == 0
    ky := 0 * 3 + 0 == 0
    y[ky==0] := x[kx==0] * x[kx==0] == 1 * 1 == 1
    y : { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    j ++ -> j == 1
3.  j == 1; j < 3
    kx := 1 * 6 + 0 == 6
    ky := 0 * 3 + 1 == 1
    y[ky==1] := x[kx==6] * x[kx==6] == 7 * 7 = 49
    y : { 1, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    j++ -> j == 2
4.  j == 2; j < 3
    kx := 2 * 6 + 0 == 12
    ky := 0 * 3 + 2 == 2
    y[ky==2] := x[kx==12] * x[kx==12] == 13 * 13 = 169
    y : { 1, 49, 169, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    j++ -> j == 3
    j < 3 FALSE. INNER LOOP END
5.  OUTER LOOP
    i++ -> i == 1
6.  Inner start
    j == 0; j < 3
    kx := 0 * 6 + 1 == 1
    ky := 1 * 3 + 0 == 3
    y[ky==3] := x[kx==1] * x[kx==1] == 2 * 2 = 4
    y : { 1, 49, 169, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

 */

void CalcMat2dSquares_cpp(int32_t* y, const int32_t* x, size_t m, size_t n)
{   // translates columns to rows

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


