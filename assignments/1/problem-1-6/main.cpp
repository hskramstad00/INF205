#include <iostream>
#include <array>

namespace
{
    void increment_at_position_by_value(int p, std::array<char, 7> arr)
    {
        std::cout << "increment_at_position_by_value(int p, std::array<char, 7> arr):\n";
        arr[p]++;
        std::cout << "\tarr inside the function: \"" << arr.data() << "\"\n";
    }

    void increment_at_position_by_reference(int p, std::array<char, 7>& arr)
    {
        std::cout << "increment_at_position_by_reference(int p, std::array<char, 7>& arr):\n";
        arr[p]++;
        std::cout << "\tarr inside the function: \"" << arr.data() << "\"\n";
    }
}

int main()
{
    std::array<char, 7> arr = { 'I', 'N', 'F', '2', '0', '5', '\0'};

    increment_at_position_by_value(5, arr);
    std::cout << "\tarr after pass-by-value call: \"" << arr.data() << "\"\n\n";

    increment_at_position_by_reference(5, arr);
    std::cout << "\tarr after pass-by-reference call: \"" << arr.data() << "\"\n";
}