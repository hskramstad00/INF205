#include <iostream>

using namespace std;

class Rectangle
{

    private:
        double length;
        double width;

        double area()
        {
            return length * width;
        }

    public:

        void set_dimensionds (double l, double w)
        {
            length = l;
            width = w;
        }

        double perimeter();

        void print_area()
        {
            cout << "Area: " << area() << '\n';
        }


};

double Rectangle::perimeter()
{
    return 2 * (length + width);
}

int main()
{
    Rectangle rectangle1;

    rectangle1.set_dimensionds(10, 20);

    cout << "Perimeter: " << rectangle1.perimeter() << '\n';

    rectangle1.print_area();

    return 0;
}