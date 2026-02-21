#include "book-index.h"
#include <iostream>

using namespace litindex;

/* Remark: Not good style. See Core Guidelines C.49 for better style. */
BookIndex::BookIndex(int c, int s, int p)
{
   this->set_chapter(c);
   this->set_section(s);
   this->set_page(p);
}

/*
 * goes to next chapter, returns new chapter number
 * this implementation also automatically goes to the next page
 */
int BookIndex::next_chapter()
{
   this->chapter++;
   this->section = 1;
   this->page++;
   return chapter;
}

/*
 * goes to next section, returns new section number
 */
int BookIndex::next_section()
{
   this->section++;
   return section;
}

/*
 * goes to next page, returns new page number
 */
int BookIndex::next_page()
{
   this->page++;
   return page;
}

/*
 * write to stdout
 */
void BookIndex::out() const
{
   std::cout << "Section " << this->chapter << "." << this->section << ", p. " << this->page << "\n";
}
