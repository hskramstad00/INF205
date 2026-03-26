#include <iostream>

// adding a forward declaration here fro add, whic is is defined in add.cpp
// since main.cpp here doesn't now what add is jet.
int add(int x, int y);

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3,4) << '\n';

    return 0;
}