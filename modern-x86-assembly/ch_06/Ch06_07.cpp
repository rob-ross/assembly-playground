//  Ch06_07.cpp
//
//  Created by Rob Ross on 9/28/26.

#include <cmath>
#include <iostream>
#include <iomanip>


// Ch06_07_fasm.asm
extern "C" bool CalcBSA_avx(const double* ht, const double* wt, int n,
    double* bsa1, double* bsa2, double* bsa3, double* bsa_mean);

// Ch06_07_fcpp.cpp
extern bool CalcBSA_cpp(const double* ht, const double* wt, int n,
    double* bsa1, double* bsa2, double* bsa3, double* bsa_mean);


bool CalcBSA_cpp(const double* ht, const double* wt, int n, double* bsa1,
    double* bsa2, double* bsa3, double* bsa_mean)
{
    if (n <= 0)
        return false;

    for (int i = 0; i < n; i++)
    {
        bsa1[i] = 0.007184 * pow(ht[i], 0.725) * pow(wt[i], 0.425);
        bsa2[i] = 0.0235 * pow(ht[i], 0.42246) * pow(wt[i], 0.51456);
        bsa3[i] = sqrt(ht[i] * wt[i] / 3600.0);

        bsa_mean[i] = (bsa1[i] + bsa2[i] + bsa3[i]) / 3.0;
    }

    return true;
}


int main()
{
    constexpr int n = 6;
    constexpr double ht[n] = { 150, 160, 170, 180, 190, 200 };
    constexpr double wt[n] = { 50.0, 60.0, 70.0, 80.0, 90.0, 100.0 };
    double bsa1_a[n], bsa1_b[n];
    double bsa2_a[n], bsa2_b[n];
    double bsa3_a[n], bsa3_b[n];
    double bsa_mean_a[n], bsa_mean_b[n];

    CalcBSA_cpp(ht, wt, n, bsa1_a, bsa2_a, bsa3_a, bsa_mean_a);
    CalcBSA_avx(ht, wt, n, bsa1_b, bsa2_b, bsa3_b, bsa_mean_b);

    constexpr int w1 = 6;
    constexpr int w2 = 7;
    constexpr char sp = ' ';

    std::cout << std::fixed;
    std::cout << "----- Results for Ch06_07 -----\n";

    for (int i = 0; i < n; i++)
    {
        std::cout << std::setprecision(1);
        std::cout << "height: " << std::setw(w1) << ht[i] << " (cm)  ";
        std::cout << "weight: " << std::setw(w1) << wt[i] << " (kg)\n";
        std::cout << std::setprecision(4);

        std::cout << "C++ | ";
        std::cout << "bas1: " << std::setw(w2) << bsa1_a[i] << sp;
        std::cout << "bas2: " << std::setw(w2) << bsa2_a[i] << sp;
        std::cout << "bsa3: " << std::setw(w2) << bsa3_a[i] << sp;
        std::cout << "bsa_mean: ";
        std::cout << std::setw(w2) << bsa_mean_a[i] << " (sq. m)\n";

        std::cout << "ASM | ";
        std::cout << "bsa1: " << std::setw(w2) << bsa1_b[i] << sp;
        std::cout << "bsa2: " << std::setw(w2) << bsa2_b[i] << sp;
        std::cout << "bsa3: " << std::setw(w2) << bsa3_b[i] << sp;
        std::cout << "bsa_mean: ";
        std::cout << std::setw(w2) << bsa_mean_b[i] << " (sq. m)\n\n";
    }
}
