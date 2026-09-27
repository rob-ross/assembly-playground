//  Ch04_04.cpp
//
//  Created by Rob Ross on 9/18/26.
//


#include <cstddef>
#include <cstdint>
#include <iostream>


// Ch04_04_fasm.asm, Ch04_04_fasm.s
extern "C" size_t CountChars_a(const char* s, char c);

// Ch04_04_fcpp.cpp
extern size_t CountChars_cpp(const char* s, char c);

// Ch04_04_misc.cpp
extern void DisplayResults(char sea_char, size_t n1, size_t n2);


size_t CountChars_cpp(const char* s, char c)
{
    size_t num_chars = 0;

    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == c)
            num_chars++;
    }

    return num_chars;
}


void DisplayResults(char sea_char, size_t n1, size_t n2)
{
    constexpr char nl = '\n';

    std::cout << "Search char: " << sea_char << " | ";
    std::cout << "Character counts: n1 = " << n1 << ", n2 = " << n2 << nl;

    if (n1 != n2) {
        std::cout << "compare check failed!\n";
    }
}


int main()
{
    const char* test_string =
    {
        "azure, beige, black, blue, brown\n"
        "cyan, gold, gray, indigo, magenta\n"
        "maroon, orange, pink, purple, red\n"
        "teal, tan, violet, white, yellow\n"
    };

    constexpr char sea_chars[] {'a', 'e', 'i', 'm', 'o', 'r', 't', 'v', 'w', 'X'};
    constexpr size_t num_sea_chars = sizeof(sea_chars) / sizeof(char);

    std::cout << "----- Results for Ch04_04 -----\n\n";

    std::cout << "Test string:\n";
    std::cout << test_string << '\n';

    for (size_t j = 0; j < num_sea_chars; j++)
    {
        size_t n1 = CountChars_cpp(test_string, sea_chars[j]);
        size_t n2 = CountChars_a(test_string, sea_chars[j]);

        DisplayResults(sea_chars[j], n1, n2);
    }

    return 0;
}
