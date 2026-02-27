#include <cmath>

class Bintre;

class Bintre
{
    Bintre(): item{NAN}, left{nullptr}, right{nullptr} {}
    Bintre(double x): item{NAN} {}
    ~Bintre(){
    }

    Bintre(const Bintre& orginal) = delete;
    Bintre& operator=(const Bintre& rhs) = delete;

private:
    double item;
    Bintre* left;
    Bintre* right;
};