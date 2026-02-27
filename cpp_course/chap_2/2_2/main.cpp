// Program for functions with return value

#include <iostream>

int getValueFromUser()
{
    std::cout << "Ener an integer: ";

    int input {};

    std::cin >> input;

    return input;                       // return the value the user entered back to the caller
}

int main()
{
    int num {getValueFromUser()};       //intialize num with the return value from get valueFromUser()

    std::cout << "Numbered doubbeled " << num *2 << '\n';

    return 0;
}