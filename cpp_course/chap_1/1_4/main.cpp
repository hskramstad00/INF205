#include <iostream>

/* 
This program will try out variable intialization
*/

int main()
{
    int width {5};          // define variable width and intialize with intial value 5 
    std::cout << width << '\n';     // prints 5

    // default intialization (no initializer)
    int a;
    std::cout << a << '\n';
     
    // traditional initialization forms:
    int b = 5; // copy-initialization (intial value after equal signs)
    int c (6); // direct-intialization (initial value in parenthesis)

    // modern intialization forms (preferred):
    int d {7}; // direct-list-intialization (intial value in braces)
    int e {}; // value intialization (empty braces)

    std::cout << e << '\n'; //testing

    return 0;
}