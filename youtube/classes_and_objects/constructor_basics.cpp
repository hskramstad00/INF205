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

        Cat (string n)
        {
            name = n;
            color = "Unknown";
            favorite_toy = "Unknown";
        }

        Cat (string n, string c, string ft = "Laser Pointer");

};

Cat::Cat(string n, string c, string ft)
{
            name = n;
            color = c;
            favorite_toy = ft;
}

int main()
{

    Cat cat1;

    cout << "Cat1.. " << '\n';
    cat1.print_cat();
    cout << '\n';

    Cat cat2("Spot");
    cout << "Cat2.." << '\n';
    cat2.print_cat();
    cout << '\n';

    Cat cat3("Garfield", "Orange", "Ball of Yarn");
    cout << "Cat3.." << '\n';
    cat3.print_cat();
    cout << '\n';

    Cat cat4("Garfield", "Orange");
    cout << "Cat4.." << '\n';
    cat4.print_cat();
    cout << '\n';

    return 0;
}