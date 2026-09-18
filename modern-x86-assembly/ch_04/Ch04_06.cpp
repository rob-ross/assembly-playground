//  Ch04_06.cpp
//
//  Created by Rob Ross on 9/18/26.
//



#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstdint>

// Ch04_06_fasm.asm, Ch04_06_fasm.s
extern "C" void CopyArrayI32_a(int32_t * b, const int32_t * a, size_t n);
extern "C" void FillArrayI64_a(const int64_t * a, int64_t fill_val, size_t n);


static void CopyArray()
{
    constexpr size_t n = 10;
    constexpr int32_t a[n] = { 10, -20, 30, 40, -50, 60, 70, -80, 90, 10 };
    int32_t b[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    CopyArrayI32_a(b, a, n);

    std::cout << "\nCopyArrayI32_a() results:\n";

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(5) << i << ": ";
        std::cout << std::setw(5) << a[i] << " ";
        std::cout << std::setw(5) << b[i] << '\n';
    }
}

static void FillArray(void)
{
    constexpr int64_t fill_val = -7;
    constexpr size_t n = 10;

    int64_t a[n] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    FillArrayI64_a(a, fill_val, n);

    std::cout << "\nFillArrayI32_a() results:\n";

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(5) << i << ": ";
        std::cout << std::setw(5) << a[i] << '\n';
    }
}

int main()
{
    std::cout << "----- Results for Ch04_06 -----\n";

    CopyArray();
    FillArray();
    return 0;
}
