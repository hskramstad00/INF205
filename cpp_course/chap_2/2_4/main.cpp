// program for using function parameters and arguments
#include <iostream>

int getValueFromUser()
{
    std::cout << "Enter an integear: ";
    int input{};
    std::cin >> input;

    return input;
}
// this function now takse an integer parameter
void printDouble(int value)
{
    std::cout << value << "Doubled is: " << value *2 << '\n';
}

int main()
{
    int num { getValueFromUser() };

    printDouble(num);

    return 0;
}