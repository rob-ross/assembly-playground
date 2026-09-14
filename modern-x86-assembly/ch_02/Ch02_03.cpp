//  Ch02_03.cpp
//
//  Created by Rob Ross on 9/14/26.
//

#include <iostream>
#include <iomanip>
#include <bitset>

// Ch02_03_fasm.asm, Ch02_03_fasm.s
extern "C" int ShiftU32_a(unsigned int* a_shl, unsigned int* a_shr, unsigned int a, unsigned int count);
// Ch02_03_misc.cpp
extern void DisplayResults(
    const char* s, int rc, unsigned int a, unsigned int count, unsigned int a_shl, unsigned int a_shr);


void DisplayResults(const char* s, int rc, unsigned int a, unsigned int count,
    unsigned int a_shl, unsigned int a_shr)
{
    constexpr int w = 10;
    constexpr char nl = '\n';
    std::bitset<32> a_bs(a);
    std::bitset<32> a_shl_bs(a_shl);
    std::bitset<32> a_shr_bs(a_shr);
    std::cout << s << nl;
    std::cout << "count: " << std::setw(w) << count << nl;
    std::cout << "a:   " << std::setw(w) << a << " (0b" << a_bs << ")" << nl;
    if (rc == 1)
    {
        std::cout << "shl: " << std::setw(w) << a_shl;
        std::cout << " (0b" << a_shl_bs << ")" << nl;
        std::cout << "shr: " << std::setw(w) << a_shr;
        std::cout << " (0b" << a_shr_bs << ")" << nl;
    }

    else
        std::cout << "Invalid shift count" << nl;
    std::cout << nl;
}

int main(void)
{
    int rc;
    unsigned int a, count, a_shl, a_shr;
    std::cout << "----- Results for Ch02_03 -----\n\n";
    a = 3119;
    count = 6;
    rc = ShiftU32_a(&a_shl, &a_shr, a, count);
    DisplayResults("Shift test #1", rc, a, count, a_shl, a_shr);
    a = 0x00800080;
    count = 4;
    rc = ShiftU32_a(&a_shl, &a_shr, a, count);
    DisplayResults("Shift test #2", rc, a, count, a_shl, a_shr);
    a = 0x80000001;
    count = 31;
    rc = ShiftU32_a(&a_shl, &a_shr, a, count);
    DisplayResults("Shift test #3", rc, a, count, a_shl, a_shr);
    a = 0x55555555;
    count = 32;
    rc = ShiftU32_a(&a_shl, &a_shr, a, count);
    DisplayResults("Shift test #4", rc, a, count, a_shl, a_shr);
    return 0;
}
