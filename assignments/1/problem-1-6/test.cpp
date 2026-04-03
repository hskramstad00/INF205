/*
 * Example to show the contrast between C and C++ strings:
 * 
 * C strings are of type char*, they are character arrays;
 * since arrays are pointers, they are always passed by reference.
 * It is impossible to pass them by value.
 * 
 * C++ strings are of type std::string and can be passed by value.
 */

#include <iostream>
#include <string>

namespace
{
   void increment_at_position(int p, char* str)
   {
      std::cout << "increment_at_position(int p, char* str):\n";
      str[p]++;
      std::cout << "\tstr inside the function: \"" << str << "\"\n";
   }

   void increment_at_position(int p, std::string str)
   {
      std::cout << "increment_at_position(int p, string str):\n";
      str[p]++;
      std::cout << "\tstr inside the function: \"" << str << "\"\n";
   }
}

int main()
{
   char c_style_str[] = "INF205";
   increment_at_position(5, c_style_str);
   std::cout << "\tc_style_str after the function: \"" << c_style_str << "\"\n\n";
   
   std::string cpp_style_str = "INF205";
   increment_at_position(5, cpp_style_str);
   std::cout << "\tcpp_style_str after the function: \"" << cpp_style_str << "\"\n";
}