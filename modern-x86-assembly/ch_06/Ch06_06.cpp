//  Ch06_06.cpp
//
//  Created by Rob Ross on 9/28/26.
//



#include <cstdint>
#include <iostream>
#include <iomanip>

// Ch06_06_fasm.asm
extern "C" int64_t AddIntegers_a(int8_t a, int16_t b, int32_t c, int64_t d,
    int8_t e, int16_t f, int32_t g, int64_t h);

// Ch06_06_fcpp.cpp
extern int64_t AddIntegers_cpp(int8_t a, int16_t b, int32_t c, int64_t d,
    int8_t e, int16_t f, int32_t g, int64_t h);


int64_t AddIntegers_cpp(int8_t a, int16_t b, int32_t c, int64_t d,
    int8_t e, int16_t f, int32_t g, int64_t h)
{
    return a + b + c + d + e + f + g + h;
}



int main()
{
    int8_t  a = 10,  e = -51;
    int16_t b = -21, f = 68;
    int32_t c = -37, g = -73;
    int64_t d = 49,  h = -82;

    int64_t sum1 = AddIntegers_cpp(a, b, c, d, e, f, g, h);
    int64_t sum2 = AddIntegers_a(a, b, c, d, e, f, g, h);

    constexpr  int w = 6;
    constexpr char nl = '\n';

    std::cout << "----- Results for Ch06_06 -----\n";
    std::cout << "a:    " << std::setw(w) << (int)a << nl;
    std::cout << "b:    " << std::setw(w) << b << nl;
    std::cout << "c:    " << std::setw(w) << c << nl;
    std::cout << "d:    " << std::setw(w) << d << nl;
    std::cout << "e:    " << std::setw(w) << (int)e << nl;
    std::cout << "f:    " << std::setw(w) << f << nl;
    std::cout << "g:    " << std::setw(w) << g << nl;
    std::cout << "h:    " << std::setw(w) << h << nl;
    std::cout << "sum1: " << std::setw(w) << sum1 << nl;
    std::cout << "sum2: " << std::setw(w) << sum2 << nl;

    return 0;
}
