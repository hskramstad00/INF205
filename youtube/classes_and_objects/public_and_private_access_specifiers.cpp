#include <iostream>
#include <string>

using namespace std;

class Employee
{
    // public class, accsessibel for anyone
    public:
        string name;

        // setter function
        void set_salary(double potential_salary)
        {
            // guarding salry, doing a check
            if (potential_salary < 0) salary = 0;
            else salary = potential_salary;
        }

        // getter function
        double get_salary()
        {
            return salary;
        }

        void print_bonus()
        {
            cout << "Bonus: " << calculate_bonus() << '\n';
        }
    
    // only accessibel for the class members
    private:
        // having this private means we can "guard it", having checks before allowing to set it
        double salary;

        double calculate_bonus()
        {
            return salary * 0.10;
        }
};

int main()
{
    Employee employee1;
    employee1.name = "Kevin";
    cout << employee1.name << '\n';

    employee1.set_salary(50000);
    cout << "Salary: " << employee1.get_salary() << '\n';

    employee1.print_bonus();

    return 0;
}