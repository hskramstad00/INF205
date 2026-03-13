#include <iostream>

using namespace std;

class Cat
{
    private:
        string name;
        string color;
        string favorite_toy;

    public:
        void print_cat()
        {
            cout << "Name: " << name << '\n';
            cout << "Color: " << color << '\n';
            cout << "Favourite Toy: " << favorite_toy << '\n';
        }

        // this is the constructor
        // sets the default values for the class
        Cat()
        {
            name = "Unknown";
            color = "Unokwn";
            favorite_toy = "Unown";
        }
};

int main()
{

    Cat cat1;

    cout << "Cat1.. " << '\n';
    cat1.print_cat();
    cout << '\n';

    return 0;
}