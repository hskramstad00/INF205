#include <iostream>

using namespace std;

class Number
{
    private:
        double *number;

    public:
        Number(double num)
        {
            // a pointer to a doubbel value
            // malloc is going to avocate enough space, a portion of memory where dynamic allocated data is going to go
            // and return the memory address
            // double * is going to cast thar memory adress
            // so number is going to have a pointer to a double 
            number = (double *) malloc(sizeof(double));
            // set that memory address to store the value of num
            *number = num;
            cout << "Constructur executing!" << '\n';
            // output the value of that number by dereferencing the pointer
            cout << "Number: " << *number << '\n' << '\n';
        }
    
    // destructur does clean up work
    // use the class name with tilde infornt
    // can not accept any paramters 
    // destructur is called automatically when the programs terminates
    // in generall the destructur is going to run when the object is destroyed
    ~Number()
    {
        cout << "Destructor executing!" << '\n';
        cout << "Number: " << *number << '\n' << '\n';
        // in the destructur we free the memory
        // gives back the chunk of memory
        // if we didn't do that we would have a memory leakege
        free(number);
    }

    
};

void test()
    {
        Number six(6);
    }

int main()
{

    // dynamically allocate space for objects and free that space, with new and delete operators
    // dynamically allocates space for a number object
    // five is a pointer to that object
    Number *five = new Number(5);
    // will destroy the object and free the space that the object took up. And that will call the destructur
    delete five;

    test();

    Number seven(7);


    return 0;
}