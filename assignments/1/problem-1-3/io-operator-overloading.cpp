#include "journal-article-index.h"
#include <iostream>
#include <sstream>
#include <fstream>


int main()
{
   litindex::JournalArticleIndex jai_i;
   jai_i.set_bibliographic_data(
      "IEEE_Access", 9, 0, 152333, 152346, 2021, "doi:10.1109/access.2021.3126429"
   );
   jai_i.set_page(152345);
   std::clog << "JournalArticleIndex jai_i:\n" << jai_i << "\n";

   const std::string filename = "jai_i.txt";


   std::clog << "\nWriting jai_i into file: <<filename>>.\n";
   {
        std::ofstream out(filename);
        if (!out) {
            std::cerr << "kunne ikke åpne fil for skriving: " << filename << "\n";
            return 1;
        }
        out << jai_i;  
   }

litindex::JournalArticleIndex jai_j;
std::clog << "\nReading jai_j from file: <<filename>>.\n";
{
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "kunne ikke åpne fil for lesing: " << filename << "\n";
        return 1;
    }
    in >> jai_j;
}
std::clog << "JournalArticleIndex jai_j:\n" << jai_j << "\n";

return 0;  
}