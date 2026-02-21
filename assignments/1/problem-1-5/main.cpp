#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main(int argc, char** argv)
{
    std::cout << "\nargv[0] er namnet til den k\u00F8yrbare fila: " << argv[0] << "\n";

    std::unordered_set<std::string> seen;
    std::vector<std::string> unique_args;
    unique_args.reserve(static_cast<std::size_t>(argc));

    for (int i = 0; i < argc; ++i)
    {
        std::string arg(argv[i]);

        auto [it, inserted] = seen.insert(arg);
        if (inserted)
            unique_args.push_back(std::move(arg));
    }

    for (const auto& a : unique_args)
        std::cout << "\targument: \"" << a << "\"\n";

    return 0;
}