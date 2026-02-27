// Program for writing a user defined function


#include <iostream>

void doPrint()
{
    std::cout << "Printing in doPrint()" << '\n';
}

int main()
{
    std::cout << "Starting main" << '\n';

    // calling on the function
    doPrint();

    std::cout << "Eding main" << '\n';

    return 0;
}