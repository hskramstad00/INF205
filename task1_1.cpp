#include <iostream>
#include <cstddef>  // std::ptrdiff_t


int main() {
    std::cout <<"størrelser (bytes):\n";
    std::cout <<"char: " << sizeof(char) << '\n';
    std::cout <<"short: " << sizeof(short) << '\n';
    std::cout <<"int: " << sizeof(int) << '\n';
    std::cout <<"long: " << sizeof(long) << '\n';
    std::cout <<"long long: " << sizeof(long long) << '\n';
    std::cout <<"float: " << sizeof(float) << '\n';
    std::cout <<"double: " << sizeof(double) << '\n';
    std::cout <<"long double: " << sizeof(long double) << '\n';
    std::cout <<"bool: " << sizeof(bool) << '\n';
    std::cout <<"void*: " << sizeof(void*) << '\n';

int arr[2]= {0, 0};
int* p = &arr[0];

char*b0= reinterpret_cast<char*>(p);
++p;
char* b1 = reinterpret_cast<char*>(p);

std::ptrdiff_t diff = b1 - b0;

std::cout << "Verifikasjon (int):\n";
std::cout << "sizeof(int): " << sizeof(int) << "bytes\n";
std::cout << "Byte-avstand mellom p og (p++): "<< diff << " bytes\n";

if (diff ==static_cast<std::ptrdiff_t>(sizeof(int))) {
    std::cout << "OK: diff stemmer med sizeof(int).\n";
} else {
    std::cout << "FEIL: diff stemmer ikke med sizeof(int).\n";


}

return 0;
}
