//  Ch03_03.cpp
//
//  Created by Rob Ross on 9/16/26.
//

#include <iostream>
#include <iomanip>
#include <cstdint>


// Ch03_03_fasm.asm, Ch03_03_fasm.s
extern "C" int g_NumPrimes_a;
extern "C" int g_SumPrimes_a;

extern "C" int MemAddressing_a(int32_t i, int32_t* v1, int32_t* v2,
    int32_t* v3, int32_t* v4);

// Ch03_03_misc.cpp
extern void DisplayResults(int32_t i, int32_t rc, int32_t v1, int32_t v2,
    int32_t v3, int32_t v4);

void DisplayResults(int32_t i, int32_t rc, int32_t v1, int32_t v2,
    int32_t v3, int32_t v4)
{
    constexpr int w = 5;
    constexpr char nl = '\n';
    const char* delim = ", ";

    std::cout << "i  = " << std::setw(w - 1) << i << delim;
    std::cout << "rc = " << std::setw(w - 1) << rc << delim;
    std::cout << "v1 = " << std::setw(w) << v1 << delim;
    std::cout << "v2 = " << std::setw(w) << v2 << delim;
    std::cout << "v3 = " << std::setw(w) << v3 << delim;
    std::cout << "v4 = " << std::setw(w) << v4 << nl;

    if (!(v1 == v2 && v2 == v3 && v3 == v4))
        std::cout << "validation test failed, i = " << i << nl;
}

int main()
{
    std::cout << "----- Results for Ch03_03 -----\n";

    // copy assign 0 to g_SumPrimes_a (defined in assembly language file)
    g_SumPrimes_a = 0; // copy assignment

    for (int i = -1; i < g_NumPrimes_a + 1; i++)
    {
        int32_t v1 = -1, v2 = -1, v3 = -1, v4 = -1;
        int32_t rc = MemAddressing_a(i, &v1, &v2, &v3, &v4);

        DisplayResults(i, rc, v1, v2, v3, v4);
    }

    std::cout << "\ng_SumPrimes_a = " << g_SumPrimes_a << '\n';
    return 0;
}
