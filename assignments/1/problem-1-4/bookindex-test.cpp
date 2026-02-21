#include "book-index.h"
#include <iostream>
#include <fstream>  // Required for file operations
#include <vector>   // To store multiple BookIndex objects

int main()
{
    std::ifstream infile("data.txt"); // Replace with your filename
    if (!infile) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    int count;
    if (!(infile >> count)) return 0; // Read the first line (number of objects)

    std::vector<litindex::BookIndex> indices;
    indices.reserve(count); // Efficiency boost

    for (int i = 0; i < count; ++i) {
        int c, s, p;
        if (infile >> c >> s >> p) {
            // Create object and add to vector
            indices.emplace_back(c, s, p);
        }
    }

    std::cout << "\nLoaded " << indices.size() << " BookIndex objects:\n";
    for (const auto& idx : indices) {
        idx.out();
    }

    return 0;
}