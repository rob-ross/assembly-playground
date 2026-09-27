//  Ch05_03.cpp
//
//  Created by Rob Ross on 9/26/26.
//

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <numbers>

// Ch05_03_fasm.asm, Ch05_03_fasm.s
extern "C" void CalcSphereVolSA_avx(double* vol, double* sa, double r);

// Ch05_03_fcpp.cpp
extern "C" double g_F64_PI;
extern void CalcSphereVolSA_cpp(double* vol, double* sa, double r);

extern void DisplayResults(size_t i, double r, double vol1, double sa1,
    double vol2, double sa2)
{
    constexpr int w1 = 6;
    constexpr int w2 = 9;
    constexpr char sp = ' ';

    std::cout << "i: " << i << sp;
    std::cout << "r: " << std::setw(w1) << r << sp;
    std::cout << "vol1: " << std::setw(w2) << vol1 << sp;
    std::cout << "vol2: " << std::setw(w2) << vol2 << sp;
    std::cout << "sa1: " << std::setw(w2) << sa1 << sp;
    std::cout << "sa2: " << std::setw(w2) << sa2 << '\n';
}

double g_F64_PI = std::numbers::pi_v<double>;     // used in asm code

void CalcSphereVolSA_cpp(double* vol, double* sa, double r)
{
    double sa_temp = 4.0 * std::numbers::pi_v<double> * r * r;
    double vol_temp = sa_temp * r / 3.0;

    *sa = sa_temp;
    *vol = vol_temp;
}



int main()
{
    constexpr double r_vals[] = { 0.0, 1.0, 2.0, 3.0, 5.0, 10.0, 15.0, 20.0 };
    constexpr size_t n = sizeof(r_vals) / sizeof(double);

    std::cout << "----- Results for Ch05_03 -----\n";
    std::cout << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < n; i++)
    {
        double vol1, sa1;
        double vol2, sa2;

        CalcSphereVolSA_cpp(&vol1, &sa1, r_vals[i]);
        CalcSphereVolSA_avx(&vol2, &sa2, r_vals[i]);
        DisplayResults(i, r_vals[i], vol1, sa1, vol2, sa2);
    }

    return 0;
}
