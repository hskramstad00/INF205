#include <iostream>
using namespace std;

char HexDigit(int x){
    if (x < 10) return '0' + x;
    return 'a' + (x - 10);
}

void PrintBytes(const void* ptr, size_t size){
    const unsigned char* p =
        reinterpret_cast<const unsigned char*>(ptr);


    for (size_t i=0; i < size; ++i){ 
        unsigned char c = p[i];
        cout  << "0x"
            << HexDigit(c / 16)
            << HexDigit(c % 16)
            << " ";
    }
    cout << "\n";
}

int main(){
    short s = -12;
    int i = -12;
    long l = -12;
    long long ll = -12;

    cout << "short: ";
    PrintBytes(&s, sizeof(s));

    cout << "int: ";
    PrintBytes(&i, sizeof(i));

    cout << "long: ";
    PrintBytes(&l, sizeof(l));

    cout << "long long: ";
    PrintBytes(&ll, sizeof(ll));

    return 0;
}