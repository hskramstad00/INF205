#include <iostream>

using namespace std;

class Foo
{

    private:
    int* array, size;

    public:
    Foo(int s)
    {
        size = s;
        array = new int[size] {0};

    }
    
    ~Foo()
    {
        if(array)
            delete [] array;    
    
    }

    int& operator[] (int i)
    { return array[i];}

};

int main()
{
    cin.get();
    return 0;
}