#include "../include/process.hpp"
#include "fcntl.h"

bool is_vowel(char e) {
  if (e != 'a' &&  e != 'A' && e != 'e' && e != 'E' && 
        e != 'i' && e != 'I' && e != 'o' && e != 'O' && e != 'U' &&
        e != 'u' && e != 'y' && e != 'Y') {

    return false;
  }

  return true;
}

void process_handler() {
 std::string buf;

  while(true) {
    getline(std::cin, buf);
    std::string new_str;

    for (auto& e : buf) {
      if (!is_vowel(e)) {
        new_str.push_back(e);
      }
    }

    std::cout << new_str.c_str() << std::endl;
  }
}
