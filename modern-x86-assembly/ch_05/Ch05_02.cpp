//  Ch05_02.cpp
//
//  Created by Rob Ross on 9/26/26.
//

#include <cstddef>
#include <cmath>
#include <numbers>
#include <iostream>
#include <iomanip>


// Ch05_02_fasm.asm, Ch05_02_fasm.s
extern "C" void CalcConeVolSA_avx(float* vol, float* sa, float r, float h);

// Ch05_02_fcpp.cpp
extern "C" float g_F32_PI;
extern void CalcConeVolSA_cpp(float* vol, float* sa, float r, float h);

// Ch05_02_misc.cpp
extern void DisplayResults(size_t i, float r, float h, float vol1, float sa1,
    float vol2, float sa2);



float g_F32_PI = std::numbers::pi_v<float>;     // used in asm code

void CalcConeVolSA_cpp(float* vol, float* sa, float r, float h)
{
    constexpr float pi = std::numbers::pi_v<float>;

    *vol = pi * r * r * h / 3.0f;
    *sa = pi * r * (r + sqrt(r * r + h * h));
}


void DisplayResults(size_t i, float r, float h, float vol1, float sa1, float vol2, float sa2)
{
    constexpr int w1 = 4;
    constexpr int w2 = 8;
    constexpr char sp = ' ';

    std::cout << "i: " << i << sp;
    std::cout << "r: " << std::setw(w1) << r << sp;
    std::cout << "h: " << std::setw(w1) << h << sp;
    std::cout << "vol1: " << std::setw(w2) << vol1 << sp;
    std::cout << "vol2: " << std::setw(w2) << vol2 << sp;
    std::cout << "sa1: " << std::setw(w2) << sa1 << sp;
    std::cout << "sa2: " << std::setw(w2) << sa2 << '\n';
}

int main()
{
    constexpr float r_vals[] { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
    constexpr float h_vals[] { 1.0f, 3.5f, 4.0f, 6.5f, 8.0f };
    constexpr size_t n = sizeof(r_vals) / sizeof(float);

    std::cout << "----- Results for Ch05_02 -----\n";
    std::cout << std::fixed << std::setprecision(3);

    for (size_t i = 0; i < n; i++)
    {
        float vol1, sa1;
        float vol2, sa2;
        float r = r_vals[i];
        float h = h_vals[i];

        CalcConeVolSA_cpp(&vol1, &sa1, r, h);
        CalcConeVolSA_avx(&vol2, &sa2, r, h);
        DisplayResults(i, r, h, vol1, sa1, vol2, sa2);
    }

    return 0;
}
