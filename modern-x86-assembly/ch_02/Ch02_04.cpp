//  Ch02_04.cpp
//
//  Created by Rob Ross on 9/14/26.
//

#include <iostream>

// Ch02_04_fasm.asm, Ch02_04_fasm.s
extern "C" long long AddSubI64a_a(long long a, long long b, long long c,
    long long d);
extern "C" long long AddSubI64b_a(long long a, long long b, long long c,
    long long d);



namespace {

    void DisplayResults(const char* msg, long long a, long long b, long long c,
                        long long d, long long r1, long long r2)
    {
        constexpr char nl = '\n';
        std::cout << msg << nl;
        std::cout << "a =" << a << nl;
        std::cout << "b =" << b << nl;
        std::cout << "c =" << c << nl;
        std::cout << "d =" << d << nl;
        std::cout << "r1 = " << r1 << nl;
        std::cout << "r2 = " << r2 << nl;
        std::cout << nl;
    }

}

int main()
{
    long long a = 10;
    long long b = 40;
    long long c = 9;
    long long d = 6;
    long long r1, r2;
    std::cout << "----- Results for Ch02_04 -----\n\n";
    r1 = (a + b) - (c + d) + 7;
    r2 = AddSubI64a_a(a, b, c, d);
    DisplayResults("Results for AddSubI64a_a()", a, b, c, d, r1, r2);
    b *= -10000000000;
    r1 = (a + b) - (c + d) + 12345678900;
    r2 = AddSubI64b_a(a, b, c, d);
    DisplayResults("Results for AddSubI64b_a()", a, b, c, d, r1, r2);
    return 0;
}
