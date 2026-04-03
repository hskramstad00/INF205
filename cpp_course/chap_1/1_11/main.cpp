#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";

    int num {};
    std::cin >> num;

    std::cout << "The dobbel of that number is " << num *2 << '\n';

    std::cout << "The trippel of that number is " << num *3 << '\n';

    return 0;
}