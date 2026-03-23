#include <iostream>

int main()
{
    int a= 1;
    int b = 2;
    int temp = a;
    a = b;
    b = temp;
    // to swap two variables, we need a temporary variable to hold
    // the value of one of the variables while we assign the other variables value to it.
    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";

    return 0;
}