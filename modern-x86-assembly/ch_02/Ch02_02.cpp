//  Ch02_02.cpp
//
//  Created by Rob Ross on 9/14/26.
//
//

#include <iostream>
#include <iomanip>

// Ch02_02_fasm.asm, Ch02_02_fasm.s
extern "C" unsigned int BitOpsU32_a(unsigned int a, unsigned int b,
    unsigned int c, unsigned int d);
// Ch02_02_fcpp.cpp
unsigned int BitOpsU32_cpp(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d);
// Ch02_02_misc.cpp
extern void DisplayResults(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d, unsigned int r1, unsigned int r2);

unsigned int BitOpsU32_cpp(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d)
{
    // Calculate ~(((a & b) | c ) ^ d)
    unsigned int t1 = a & b;
    unsigned int t2 = t1 | c;
    unsigned int t3 = t2 ^ d;
    unsigned int result = ~t3;
    return result;
}



void DisplayResults(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d, unsigned int r1, unsigned int r2)
{
    constexpr int w = 8;
    constexpr char nl = '\n';
    std::cout << "----- Results for Ch02_02 -----\n";
    std::cout << std::setfill('0');
    std::cout << "a =0x" << std::hex << std::setw(w) << a << nl;
    std::cout << "b =0x" << std::hex << std::setw(w) << b << nl;
    std::cout << "c =0x" << std::hex << std::setw(w) << c << nl;
    std::cout << "d =0x" << std::hex << std::setw(w) << d << nl;
    std::cout << "r1 = 0x" << std::hex << std::setw(w) << r1 << nl;
    std::cout << "r2 = 0x" << std::hex << std::setw(w) << r2 << nl;
    std::cout << nl;
    if (r1 != r2)
        std::cout << "Compare check failed" << nl;
}

int main()
{
    unsigned int a = 0xffffffff;
    unsigned int b = 0x12345678;
    unsigned int c = 0x87654321;
    unsigned int d = 0x55555555;
    unsigned int r1 = BitOpsU32_cpp(a, b, c, d);
    unsigned int r2 = BitOpsU32_a(a, b, c, d);
    DisplayResults(a, b, c, d, r1, r2);
    return 0;
}
