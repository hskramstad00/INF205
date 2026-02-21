#include <iostream>
#include <string>
#include <unordered_set>

int main(int argc, char** argv)
{
    std::unordered_set<std::string> seen;

    for (int i = 0; i < argc; ++i) {
        std::string s = argv[i];
        if (seen.insert(s).second) {         
            std::cout << "argument: \"" << s << "\"\n";
        }
    }
}