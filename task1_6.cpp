#include <array>
#include <iostream>

void increment_by_value(int p, std::array<char, 7> str) {  
    std::cout << "by value:\n";
    str[p]++;
    std::cout << "\tinside: \"" << str.data() << "\"\n";
}

void increment_by_reference(int p, std::array<char, 7>& str) { 
    std::cout << "by reference:\n";
    str[p]++;
    std::cout << "\tinside: \"" << str.data() << "\"\n";
}

int main() {
    std::array<char, 7> a = {'I','N','F','2','0','5','\0'};

    increment_by_value(5, a);
    std::cout << "after value call: \"" << a.data() << "\"\n\n";

    increment_by_reference(5, a);
    std::cout << "after reference call: \"" << a.data() << "\"\n";
}

