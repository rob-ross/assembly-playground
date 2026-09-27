//  Ch05_01.cpp
//
//  Created by Rob Ross on 9/25/26.
//

#include <iostream>
#include <iomanip>

// Ch05_01_fasm.asm, Ch05_01_fasm.s
extern "C" float ConvertFtoC_avx(float deg_f);
extern "C" float ConvertCtoF_avx(float deg_c);



static void ConvertFtoC()
{
    constexpr int w = 10;
    constexpr float deg_fvals[] =
    {
        -459.67f, -40.0f, 0.0f, 32.0f, 72.0f, 98.6f, 212.0f
    };
    constexpr size_t n = sizeof(deg_fvals) / sizeof(float);

    std::cout << "\n--- ConvertFtoC_avx() results ---\n";
    std::cout << std::fixed << std::setprecision(4);

    for (size_t i = 0; i < n; i++)
    {
        float deg_c = ConvertFtoC_avx(deg_fvals[i]);

        std::cout << "  i: " << i << "  ";
        std::cout << "f: " << std::setw(w) << deg_fvals[i] << "  ";
        std::cout << "c: " << std::setw(w) << deg_c << '\n';
    }
}

static void ConvertCtoF()
{
    constexpr int w = 10;
    constexpr float deg_cvals[] =
    {
        -273.15f, -40.0f, -17.777778f, 0.0f, 25.0f, 37.0f, 100.0f
    };
    constexpr size_t n = sizeof(deg_cvals) / sizeof(float);

    std::cout << "\n--- ConvertCtoF_avx() results ---\n";
    std::cout << std::fixed << std::setprecision(4);

    for (size_t i = 0; i < n; i++)
    {
        float deg_f = ConvertCtoF_avx(deg_cvals[i]);

        std::cout << "  i: " << i << "  ";
        std::cout << "c: " << std::setw(w) << deg_cvals[i] << "  ";
        std::cout << "f: " << std::setw(w) << deg_f << '\n';
    }
}

int main()
{
    std::cout << "----- Results for Ch05_01 -----\n";

    ConvertFtoC();
    ConvertCtoF();
    return 0;
}
