#include <iostream>
#include "quiz_4.h"

// write a compelte program that reads an integear from the user, doubels it using the 
// function from quiz_4, and prints the doubel value to the console

// la til makefile slik at man kjøre den for å kjøre både quiz5 og quiz4 sammen

int getValueFromUser()
{
    int input {};
    std::cout << "Input an integear and we wil doubel it" << '\n';
    std:: cin >> input;

    return input;
}

int main()
{   
    int value {getValueFromUser()};

    std::cout << "The doubbel of your number is: " << doubelNumber(value) << '\n';

    return 0;
}