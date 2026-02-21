#include "book-index.h"
#include <iostream>
#include <fstream>  
#include <vector>   

int main()
{
    std::ifstream infile("data.txt"); 
    if (!infile) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    int count;
    if (!(infile >> count)) return 0; 

    std::vector<litindex::BookIndex> indices;
    indices.reserve(count); 

    for (int i = 0; i < count; ++i) {
        int c, s, p;
        if (infile >> c >> s >> p) {
            
            indices.emplace_back(c, s, p);
        }
    }

    std::cout << "\nLoaded " << indices.size() << " BookIndex objects:\n";
    for (const auto& idx : indices) {
        idx.out();
    }

    return 0;
}