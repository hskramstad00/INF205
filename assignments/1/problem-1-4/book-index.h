#pragma once

#include <cassert>
#include <iostream>

namespace litindex
{
   class BookIndex
   {
   public:
      BookIndex() = default;
      BookIndex(int c, int s, int p);  
      ~BookIndex()
      {
         std::cout << "Deallocating.\n";
      }
      
      int get_chapter() const { return this->chapter; }
      int get_section() const { return this->section; }
      int get_page() const { return this->page; }
      
      void set_chapter(int c) { assert(c >= 0); this->chapter = c; }
      void set_section(int s) { assert(s >= 0); this->section = s; }
      void set_page(int p) { assert(p >= 0); this->page = p; }
      
      int next_chapter();  /* goes to next chapter, returns new chapter number */
      int next_section();  /* goes to next section, returns new section number */
      int next_page();     /* goes to next page, returns new page number */
   
      void out() const;    /* output status information */
   
   private:
      int chapter{};
      int section{};
      int page{};
   };
}
