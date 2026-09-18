//  Ch03_02.cpp
//
//  Created by Rob Ross on 9/14/26.
//

#include <cstdint>
#include <iostream>

// Ch03_01_fasm.asm, Ch03_01_fasm.s
extern "C" int64_t CalcResultI64_a(int8_t a, int16_t b, int32_t c, int64_t d,
    int8_t e, int16_t f, int32_t g, int64_t h);
extern "C" void CalcResultU64_a(uint8_t a, uint16_t b, uint32_t c, uint64_t d,
    uint8_t e, uint16_t f, uint32_t g, uint64_t h, uint64_t* quo, uint64_t* rem);

void DisplayResults(int8_t a, int16_t b, int32_t c, int64_t d,
    int8_t e, int16_t f, int32_t g, int64_t h, int64_t prod1, int64_t prod2)
{
    constexpr char nl = '\n';
    std::cout << "\nCalcResultI64 results\n";
    std::cout << "a = " << (int)a << ", b = " << b << ", c = " << c;
    std::cout << ", d = " << d << ", e = " << (int)e << ", f = " << f;
    std::cout << ", g = " << g << ", h = " << h << nl;
    std::cout << "prod1 = " << prod1 << nl;
    std::cout << "prod2 = " << prod2 << nl;
}

void DisplayResults(uint8_t a, uint16_t b, uint32_t c, uint64_t d,
    uint8_t e, uint16_t f, uint32_t g, uint64_t h,
    uint64_t quo1, uint64_t rem1, uint64_t quo2, uint64_t rem2)
{
    constexpr char nl = '\n';

    std::cout << "\nCalcResultU64 results\n";
    std::cout << "a = " << (unsigned)a << ", b = " << b << ", c = " << c;
    std::cout << ", d = " << d << ", e = " << (unsigned)e << ", f = " << f;
    std::cout << ", g = " << g << ", h = " << h << nl;
    std::cout << "quo1 = " << quo1 << ", rem1 = " << rem1 << nl;
    std::cout << "quo2 = " << quo2 << ", rem2 = " << rem2 << nl;
}

static void CalcResultI64()
{
    int8_t  a = 2,  e = 3;
    int16_t b = -3, f = -7;;
    int32_t c = 8,  g = -5;
    int64_t d = 4,  h = 10;
    // Calculate (a * b * c * d) + (e * f * g * h)
    int64_t prod1 = ((int64_t)a * b * c * d) + ((int64_t)e * f * g * h);
    int64_t prod2 = CalcResultI64_a(a, b, c, d, e, f, g, h);
    DisplayResults(a, b, c, d, e, f, g, h, prod1, prod2);
}
static void CalcResultU64()
{
    uint8_t  a = 12,            e = 101;
    uint16_t b = 17,            f = 37;
    uint32_t c = 71000000,      g =25;
    uint64_t d = 90000000000,   h = 5;
    uint64_t quo1, rem1;
    uint64_t quo2, rem2;
    // Calculate quotient and remainder for (a + b + c + d) / (e + f + g + h)
    quo1 = ((uint64_t)a + b + c + d) / ((uint64_t)e + f + g + h);
    rem1 = ((uint64_t)a + b + c + d) % ((uint64_t)e + f + g + h);
    CalcResultU64_a(a, b, c, d, e, f, g, h, &quo2, &rem2);
    DisplayResults(a, b, c, d, e, f, g, h, quo1, rem1, quo2, rem2);
}

int main()
{
    std::cout << "----- Results for Ch03_02 -----\n";
    CalcResultI64();
    CalcResultU64();
    return 0;
}
