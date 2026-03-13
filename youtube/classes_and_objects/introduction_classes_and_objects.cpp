#include <iostream>
#include <string>

using namespace std;

class BaknAccount
{
public:
    string name;
    int balance;

    void withdraw(int amount)
    {
        balance = balance - amount;
    }

    void print()
    {
        cout << name << " Has " << balance << " dollars" << '\n';
    }

};

int main()
{

    BaknAccount account1;
    account1.name = "Håkon";
    account1.balance = 3000;


    account1.print();

    BaknAccount account2;
    account2.name = "Xavi";
    account2.balance = 20000;

    account2.print();
    account2.withdraw(1000);
    account2.print();

    return 0;
}