#include <iostream>

// Program for using cout and cin

int main()
{
    std::cout << "Enter two numbers seperated by a space : ";

    // need to define variabeles first
    int x {};
    int y {};

    std::cin >> x >> y;

    std::cout << "You entered: " << x << " and: " <<y << '\n';

    return 0;
}