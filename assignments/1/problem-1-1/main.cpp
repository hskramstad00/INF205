#include <iostream>
using namespace std;

int main(){
    short ShortType;
    int IntType;
    long LongType;
    long long LongLongType;

    // Calculate and Print out

    // For short
    cout <<  "Size of short is: " << sizeof(ShortType)
         << "\n";

    // For int
    cout << "Size of int is: " << sizeof(IntType)
         << "\n";

    // For long
    cout << "Size of long is: " << sizeof(LongType)
         << "\n";

    // For long long
    cout << "Size of long long is: " <<sizeof(LongLongType)
         << "\n";

    int x;
    int* p = &x;

    cout << "Adress p : " << p << "\n";

    cout << "Adress p +1 : " << p +1 << "\n";

    cout << "Distance in bytes: "
         << reinterpret_cast<char*>(p+1) - reinterpret_cast<char*>(p)
         << "\n";

    return 0;
}