//  Ch03_04.cpp
//
//  Created by Rob Ross on 9/16/26.
//

#include <cstdint>
#include <iostream>
#include <iomanip>


// Ch03_04_fasm.asm, Ch03_04_fasm.s
extern "C" int32_t SignedMin1_a(int32_t a, int32_t b, int32_t c);
extern "C" int32_t SignedMin2_a(int32_t a, int32_t b, int32_t c);
extern "C" int32_t SignedMax1_a(int32_t a, int32_t b, int32_t c);
extern "C" int32_t SignedMax2_a(int32_t a, int32_t b, int32_t c);

void DisplayResults(const char* s1, int32_t a, int32_t b, int32_t c,
    int32_t result) {
    constexpr int w = 4;
    std::cout << s1 << "(";
    std::cout << std::setw(w) << a << ", ";
    std::cout << std::setw(w) << b << ", ";
    std::cout << std::setw(w) << c << ") = ";
    std::cout << std::setw(w) << result << '\n';
}



int main(void)
{
    constexpr int32_t a_vals[] { 2,   -3,  17, -47 };
    constexpr int32_t b_vals[] { 15, -22,  37, -16 };
    constexpr int32_t c_vals[] { 8,   28, -11,  -9 };
    constexpr int n = sizeof(a_vals) / sizeof(int32_t);

    std::cout << "----- Results for Ch03_04 -----\n";

    for (int i = 0; i < n; i++)
    {
        int32_t a = a_vals[i], b = b_vals[i], c = c_vals[i];

        int32_t smin1 = SignedMin1_a(a, b, c);
        int32_t smin2 = SignedMin2_a(a, b, c);
        int32_t smax1 = SignedMax1_a(a, b, c);
        int32_t smax2 = SignedMax2_a(a, b, c);

        std::cout << "\n------------- Example #" << i + 1 << " -------------\n";
        DisplayResults("SignedMin1_a", a, b, c, smin1);
        DisplayResults("SignedMin2_a", a, b, c, smin2);
        DisplayResults("SignedMax1_a", a, b, c, smax1);
        DisplayResults("SignedMax2_a", a, b, c, smax2);
    }

    return 0;
}
