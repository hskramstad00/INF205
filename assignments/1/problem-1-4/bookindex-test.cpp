#include "book-index.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace
{
   void start_chapter(litindex::BookIndex b)
   {
      std::cout << "start_chapter(litindex::BookIndex b)\n";

      b.next_chapter();
      b.out();  // print status
   }
}


int main()
{
   std::ifstream file("data.txt");
   if (!file)
   {
      std::cerr << "Could not open data.txt\n";
      return 1;
   }

   int n = 0;
   if (!(file >> n) || n < 0)
   {
      std::cerr << "Bad first line (expected a non-negative integer)\n";
      return 1;
   }

   std::vector<litindex::BookIndex> v;
   v.reserve(static_cast<size_t>(n));

   for (int i = 0; i < n; ++i)
   {
      litindex::BookIndex b;
      if (!(file >> b))
      {
         std::cerr << "Bad object on line " << (i + 2) << "\n";
         return 1;
      }
      v.push_back(b);
   }

   std::cout << "Read " << v.size() << " objects:\n";
   for (const auto& b : v)
      std::cout << b << "\n";
}