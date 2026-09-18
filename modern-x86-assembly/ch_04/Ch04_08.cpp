//  Ch04_08.cpp
//
//  Created by Rob Ross on 9/18/26.
//

#include <iostream>
#include <cstddef>
#include <cstdint>


// Test structure

struct TestStruct
{
    int8_t  Val8;
    int64_t Val64;
    int16_t Val16;
    int32_t Val32;
};

// Ch04_08_fasm.asm, Ch04_08_fasm.s
extern "C" int64_t SumStructVals_a(const TestStruct* ts);

// Ch04_08_misc.cpp
extern void DisplayResults(const TestStruct& ts, int64_t sum1, int64_t sum2);


void DisplayResults(const TestStruct& ts, int64_t sum1, int64_t sum2)
{
    constexpr char nl = '\n';

    std::cout << "----- Results for Ch04_08 -----\n";

    std::cout << "\n--- TestStruct Offsets ---\n";
    std::cout << "offsetof(ts.Val8):   " << offsetof(TestStruct, Val8) << nl;
    std::cout << "offsetof(ts.Val64):  " << offsetof(TestStruct, Val64) << nl;
    std::cout << "offsetof(ts.Val16):  " << offsetof(TestStruct, Val16) << nl;
    std::cout << "offsetof(ts.Val32):  " << offsetof(TestStruct, Val32) << nl;

    std::cout << "\n--- Calculated Results ---\n";
    std::cout << "ts1.Val8:   " << (int)ts.Val8 << nl;
    std::cout << "ts1.Val16:  " << ts.Val16 << nl;
    std::cout << "ts1.Val32:  " << ts.Val32 << nl;
    std::cout << "ts1.Val64:  " << ts.Val64 << nl;
    std::cout << "sum1:       " << sum1 << nl;
    std::cout << "sum2:       " << sum2 << nl;
}


int main()
{
    TestStruct ts;

    ts.Val8 = -100;
    ts.Val16 = 2000;
    ts.Val32 = -300000;
    ts.Val64 = 40000000000;

    int64_t sum1 = ts.Val8 + ts.Val16 + ts.Val32 + ts.Val64;
    int64_t sum2 = SumStructVals_a(&ts);

    DisplayResults(ts, sum1, sum2);
    return 0;
}
