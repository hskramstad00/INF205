#include <iostream>
#include <cstddef>  // size_t

char hex_digit(int v) {
    return (v < 10) ? ('0' + v) : ('a' + (v - 10));
}

void print_bytes(const void* ptr, std::size_t nbytes) {
    const unsigned char* p= reinterpret_cast<const unsigned char*>(ptr);

    for (std::size_t i = 0; i < nbytes; ++i) {
        unsigned char c = p[i];
        int hi = c/16;
        int lo = c%16;

        std::cout <<"0x" << hex_digit(hi) << hex_digit(lo);
        if (i +1 != nbytes) std::cout << " ";
    }
    std::cout << "\n";
}

template <typename T>
void demo(const char* name, T value) {
    std::cout << name << " (" << sizeof(T) << " bytes):\n";
    print_bytes(&value, sizeof(T));
}

int main() {
    short s = -12;
    int i = -12;
    long l = -12;
    long long ll = -12;

    demo("short", s);
    demo("int", i); 
    demo("long", l);
    demo("long long", ll);
    
    return 0;
}