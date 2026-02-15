#include "journal-article-index.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
   litindex::JournalArticleIndex jai_i;
   jai_i.set_bibliographic_data(
      "IEEE_Access", 9, 0, 152333, 152346, 2021, "doi:10.1109/access.2021.3126429"
   );
   jai_i.set_page(152345);
   std::clog << "JournalArticleIndex jai_i:\n" << jai_i << "\n";

   const std::string tmp_filename = "jai_tmp.txt";

   std::clog << "\nWriting jai_i into a temporary file: " << tmp_filename << "\n";

   {
      std::ofstream out(tmp_filename, std::ios::out | std::ios::trunc);
      if (!out) {
         std::cerr << "ERROR: Could not open file for writing: " << tmp_filename << "\n";
         return 1;
      }
      out << jai_i;
   }

   std::clog << "Text content of the file is now as follows:\n";
   {
      std::ifstream in(tmp_filename);
      if (!in) {
         std::cerr << "ERROR: Could not open file for reading " << tmp_filename << "\n";
         return 1;
      }
      std::string line;
      while (std::getline(in, line)) {
         std::clog << line << "\n";
      }
   }

   litindex::JournalArticleIndex jai_j;
   std::clog << "\nReading jai_j from the temporary file.\n";
   {
      std::ifstream in(tmp_filename);
      if (!in) {
         std::cerr << "ERROR: Could not open file for reading " << tmp_filename << "\n";
         return 1;
      }
      in >> jai_j;
   }

   std::clog << "JournalArticleIndex jai_j:\n" << jai_j << "\n";
}
