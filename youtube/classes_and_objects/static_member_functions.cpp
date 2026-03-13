// static member functions
// static member functions allows us to work with and manipulate static members variabels otherwise known as class variabeles

#include <iostream>

using namespace std;

class Square {
    private:
        int side_length;
        // startic member variabel
        // one total_squares variabel for the whole of the class to share
        // is called class variabel also
        static int total_squares;

        // private static function to do the incrementing of total squares
        static void incrementTotal()
        {
            total_squares++;
        }

    public:
        Square(int length)
        {
            side_length = length;
            incrementTotal();
        }

        int area()
        {
            return side_length * side_length;
        }
        
        // static member function
        // the is what the static keyword means
        
        static int getTotal()
        {
            return total_squares;

        }
};

// we're going to use this to keep track of how many square object there is
int Square::total_squares = 0;

int main()
{
    Square square1(5);

    cout << "square1 area: " << square1.area() << '\n';

    // since total_squares is a private static variabel
    // that means we can't accsess this variabel outside of the class
    // then we would need to create a static member function to access and return this value
    cout << "total squares: " << Square::getTotal() << '\n';

    Square square2(10);

    cout << "square area " << square2.area() << '\n';
    cout << "total squares: " << Square::getTotal() << '\n';

    return 0;
}