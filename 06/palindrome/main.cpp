#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------


  // Add your implementation here
  std::string::iterator first_letter = s.begin();
  std::string::iterator last = s.end();
  int length = s.length();

      // Base cases
      if (first_letter >= last) {
          return true;  // An empty string or a single character string is a palindrome.
      }

      // Check if the first and last characters match
      if (*first_letter != *prev(last)) {
          return false;
      }

      // Recursively check the substring between the first and last characters
      return palindrome_recursive(s.substr(1, length - 2));

}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
