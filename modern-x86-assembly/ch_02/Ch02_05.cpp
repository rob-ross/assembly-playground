//  Ch02_05.cpp
//
//  Created by Rob Ross on 9/14/26.
//

#include <iostream>

// Ch02_05_fasm.asm, Ch02_05_fasm.s
extern "C" void MulI32_a(int* prod1, long long* prod2, int a, int b);
extern "C" int DivI32_a(int* quo, int* rem, int a, int b);


void DisplayResults(int test_id, int a, int b, int prod1,
    long long prod2, int quo, int rem, int rc)
{
    constexpr char nl = '\n';
    std::cout << "Mul/Div test case #" << test_id << nl;
    std::cout << "a = " << a << ", b = " << b << nl;
    std::cout << "prod1 = " << prod1 << ", prod2 = " << prod2 << nl;
    if (rc == 0)
        std::cout << "error: division by zero" << nl;
    else
        std::cout << "quo = " << quo << ", rem = " << rem << nl;
    std::cout << nl;
}

int main()
{
    constexpr int a_vals[] {47, -291, 19, 247 };
    constexpr int b_vals[] {13, 7, 0, 85 };
    constexpr int n = sizeof(a_vals) / sizeof(int);
    std::cout << "----- Results for Ch02_05 -----\n\n";
    for (int i = 0; i < n; i++)
    {
        int a = a_vals[i];
        int b = b_vals[i];
        int prod1, quo, rem;
        long long prod2;
        MulI32_a(&prod1, &prod2, a, b);
        int rc = DivI32_a(&quo, &rem, a, b);
        DisplayResults(i, a, b, prod1, prod2, quo, rem, rc);
    }
    return 0;
}
