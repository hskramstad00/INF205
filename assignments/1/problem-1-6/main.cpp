/*
 * 1.6 Use of std::array
 *
 * Same idea as string-argument-passing.cpp, but using:
 *   std::array<char, 7>
 *
 * We demonstrate:
 *  - pass-by-value  (copy)    -> caller unchanged
 *  - pass-by-reference (&)    -> caller changed
 *
 * Note: We include '\0' as the last element so arr.data() can be printed
 * as a C-style string.
 */

#include <iostream>
#include <array>

namespace
{
    // Pass by VALUE (copy)
    void increment_at_position_by_value(int p, std::array<char, 7> arr)
    {
        std::cout << "increment_at_position_by_value(int p, std::array<char, 7> arr):\n";
        arr[p]++;
        std::cout << "\tarr inside the function: \"" << arr.data() << "\"\n";
    }

    // Pass by REFERENCE (modifies caller)
    void increment_at_position_by_reference(int p, std::array<char, 7>& arr)
    {
        std::cout << "increment_at_position_by_reference(int p, std::array<char, 7>& arr):\n";
        arr[p]++;
        std::cout << "\tarr inside the function: \"" << arr.data() << "\"\n";
    }
}

int main()
{
    // "INF205" plus '\0' terminator -> 7 chars total
    std::array<char, 7> arr = { 'I', 'N', 'F', '2', '0', '5', '\0' };

    // Pass by value (copy)
    increment_at_position_by_value(5, arr);
    std::cout << "\tarr after pass-by-value call: \"" << arr.data() << "\"\n\n";

    // Pass by reference (original modified)
    increment_at_position_by_reference(5, arr);
    std::cout << "\tarr after pass-by-reference call: \"" << arr.data() << "\"\n";
}