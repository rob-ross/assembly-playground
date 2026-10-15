//  Ch02_01.cpp
//
//  Created by Rob Ross on 9/14/26.
//

#include <iostream>
#include "roblib/allocator.h" // test that we can see this

extern "C" int AddSubI32_a(int a, int b, int c, int d);
extern void DisplayResults(int a, int b, int c, int d, int r1, int r2);

void DisplayResults(int a, int b, int c, int d, int r1, int r2) {
    constexpr char nl = '\n';
    std::cout << "----- Results for Ch02_01 -----\n";
    std::cout << "a =  " << a << nl;
    std::cout << "b =  " << b << nl;
    std::cout << "c =  " << c << nl;
    std::cout << "d =  " << d << nl;
    std::cout << "r1 = " << r1 << nl;
    std::cout << "r2 = " << r2 << nl;
    std::cout << nl;
}

int main() {
    int a = 10;
    int b = 40;
    int c = 9;
    int d = 6;
    int r1 = (a + b) - (c + d) + 7;
    int r2 = AddSubI32_a(a, b, c, d);
    DisplayResults(a, b, c, d, r1, r2);
    return 0;
}
