//  Ch05_04.cpp
//
//  Created by Rob Ross on 9/26/26.
//

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <limits>

// Ch05_04_fasm.asm, Ch05_04_fasm.s
extern "C" void CompareF32_avx(uint8_t* cmp_results, float a, float b);

// Ch05_04_misc.cpp
extern void DisplayResults(const uint8_t* cmp_results, float a, float b);

// Miscellaneous constants
constexpr size_t c_NumCmpOps = 7;


static const char* c_OpStrings[c_NumCmpOps] =
{
    "UO", "LT", "LE", "EQ", "NE", "GT", "GE"
};

void DisplayResults(const uint8_t* cmp_results, float a, float b)
{
    constexpr char nl = '\n';

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "a = " << a << ", b = " << b << nl;

    for (size_t i = 0; i < c_NumCmpOps; i++)
    {
        std::cout << c_OpStrings[i] << '=';
        std::cout << std::boolalpha << std::left;
        std::cout << std::setw(6) << (cmp_results[i] != 0) << ' ';
    }

    std::cout << nl << nl;
}


int main()
{
    constexpr size_t n = 6;
    float a[n] { 120.0f, 250.0f, 300.0f, -18.0f,  -81.0f, 42.0f };
    float b[n] { 130.0f, 240.0f, 300.0f,  32.0f, -100.0f,  0.0f };

    // Set NAN test value
    b[n - 1] = std::numeric_limits<float>::quiet_NaN();

    std::cout << "\n----- Results for Ch05_04 -----\n";

    for (size_t i = 0; i < n; i++)
    {
        uint8_t cmp_results[c_NumCmpOps];

        CompareF32_avx(cmp_results, a[i], b[i]);
        DisplayResults(cmp_results, a[i], b[i]);
    }
}
