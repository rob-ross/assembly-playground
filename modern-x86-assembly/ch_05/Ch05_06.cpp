//  Ch05_06.cpp
//
//  Created by Rob Ross on 9/27/26.
//

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <numbers>

// Simple union for data exchange
union Uval
{
    int32_t m_I32;
    int64_t m_I64;
    float m_F32;
    double m_F64;
};

// The order of values in enum CvtOp must match the jump table
// that's defined in the .asm or .s file.
enum class CvtOp : unsigned int
{
    I32_F32,       // int32_t to float
    F32_I32,       // float to int32_t
    I32_F64,       // int32_t to double
    F64_I32,       // double to int32_t
    I64_F32,       // int64_t to float
    F32_I64,       // float to int64_t
    I64_F64,       // int64_t to double
    F64_I64,       // double to int64_t
    F32_F64,       // float to double
    F64_F32,       // double to float
};

// Enumerated type for rounding control
enum class RC : unsigned int
{
    Nearest, Down, Up, Zero     // Do not change order
};

// Ch05_06_fasm.asm, Ch05_06_fasm.s
extern "C" bool ConvertScalar_avx(Uval* a, Uval* b, CvtOp cvt_op, RC rc);


const std::string c_RcStrings[] = { "Nearest", "Down", "Up", "Zero" };
constexpr RC c_RcVals[] = { RC::Nearest, RC::Down, RC::Up, RC::Zero };
constexpr size_t c_NumRC = sizeof(c_RcVals) / sizeof(RC);

int main(void)
{
    constexpr char nl = '\n';
    Uval src1, src2, src3, src4, src5, src6, src7;

    src1.m_F32 = std::numbers::pi_v<float>;
    src2.m_F32 = -std::numbers::e_v<float>;
    src3.m_F64 = std::numbers::sqrt2_v<double>;
    src4.m_F64 = 1.0 / std::numbers::sqrt2_v<double>;
    src5.m_F64 = std::numeric_limits<double>::epsilon();
    src6.m_I32 = std::numeric_limits<int>::max();
    src7.m_I64 = std::numeric_limits<long long>::max();

    std::cout << "----- Results for Ch05_06 -----\n";

    for (size_t i = 0; i < c_NumRC; i++)
    {
        RC rc = c_RcVals[i];
        Uval des1, des2, des3, des4, des5, des6, des7;

        ConvertScalar_avx(&des1, &src1, CvtOp::F32_I32, rc);
        ConvertScalar_avx(&des2, &src2, CvtOp::F32_I64, rc);
        ConvertScalar_avx(&des3, &src3, CvtOp::F64_I32, rc);
        ConvertScalar_avx(&des4, &src4, CvtOp::F64_I64, rc);
        ConvertScalar_avx(&des5, &src5, CvtOp::F64_F32, rc);
        ConvertScalar_avx(&des6, &src6, CvtOp::I32_F32, rc);
        ConvertScalar_avx(&des7, &src7, CvtOp::I64_F64, rc);

        std::cout << std::fixed;
        std::cout << "\nRounding control = " << c_RcStrings[(int)rc] << nl;

        std::cout << "  F32_I32: " << std::setprecision(8);
        std::cout << src1.m_F32 << " --> " << des1.m_I32 << nl;

        std::cout << "  F32_I64: " << std::setprecision(8);
        std::cout << src2.m_F32 << " --> " << des2.m_I64 << nl;

        std::cout << "  F64_I32: " << std::setprecision(8);
        std::cout << src3.m_F64 << " --> " << des3.m_I32 << nl;

        std::cout << "  F64_I64: " << std::setprecision(8);
        std::cout << src4.m_F64 << " --> " << des4.m_I64 << nl;

        std::cout << "  F64_F32: ";
        std::cout << std::setprecision(16) << src5.m_F64 << " --> ";
        std::cout << std::setprecision(8) << des5.m_F32 << nl;

        std::cout << "  I32_F32: " << std::setprecision(8);
        std::cout << src6.m_I32 << " --> " << des6.m_F32 << nl;

        std::cout << "  I64_F64: " << std::setprecision(8);
        std::cout << src7.m_I64 << " --> " << des7.m_F64 << nl;
    }

    return 0;
}
