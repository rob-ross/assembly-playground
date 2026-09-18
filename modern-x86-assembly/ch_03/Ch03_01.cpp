//  Ch03_01.cpp
//
//  Created by Rob Ross on 9/14/26.
//
#include <iostream>
#include <cstdint>

// Ch03_01_fasm.asm, Ch03_01_fasm.s
extern "C" int32_t SumValsI32_a(int32_t a, int32_t b, int32_t c, int32_t d,
    int32_t e, int32_t f, int32_t g, int32_t h);
extern "C" uint64_t MulValsU64_a(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
    uint64_t e, uint64_t f, uint64_t g, uint64_t h);

void DisplayResults(int32_t a, int32_t b, int32_t c, int32_t d,
    int32_t e, int32_t f, int32_t g, int32_t h, int32_t result1, int32_t result2)
{
    constexpr char nl = '\n';
    std::cout << "\nStack Example #1\n";
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << ' ';
    std::cout << "d = " << d << ", e = " << e << ", f = " << f << ' ';
    std::cout << "g = " << g << ", h = " << h << nl;
    std::cout << "result1 = " << result1 << ", result2 = " << result2 << nl;
}
void DisplayResults(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e,
    uint64_t f, uint64_t g, uint64_t h, uint64_t result1, uint64_t result2)
{
    constexpr char nl = '\n';
    std::cout << "\nStack Example #2\n";
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << ' ';
    std::cout << "d = " << d << ", e = " << e << ", f = " << f << ' ';
    std::cout << "g = " << g << ", h = " << h << nl;
    std::cout << "result1 = " << result1 << ", result2 = " << result2 << nl;
}

static void StackExample1()
{
    // Stack example #1 - 32-bit integers
    int32_t a = 2, b = -3, c = 8, d = 9;
    int32_t e = 3, f = -7, g = 5, h = -1000000;
    int32_t result1 = a + b + c + d + e + f + g + h;
    int32_t result2 = SumValsI32_a(a, b, c, d, e, f, g, h);
    DisplayResults(a, b, c, d, e, f, g, h, result1, result2);
}

static void StackExample2()
{
    // Stack example #2 - 64-bit integers
    uint64_t a = 10, b = 20, c = 30, d = 40;
    uint64_t e = 50, f = 60, g = 70, h = 80;
    uint64_t result1 = a * b * c * d * e * f * g * h;
    uint64_t result2 = MulValsU64_a(a, b, c, d, e, f, g, h);
    DisplayResults(a, b, c, d, e, f, g, h, result1, result2);
}

int main() {
    std::cout << "----- Results for Ch03_01 ----\n";
    StackExample1();
    StackExample2();
}
