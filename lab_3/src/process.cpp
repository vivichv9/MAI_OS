#include "process.h"

bool is_vowel(char e) {
  if (e != 'a' &&  e != 'A' && e != 'e' && e != 'E' && 
        e != 'i' && e != 'I' && e != 'o' && e != 'O' && e != 'U' &&
        e != 'u' && e != 'y' && e != 'Y') {

    return false;
  }

  return true;
}

void lab3::process_handler(void* mmf_ptr) {
  size_t size = strlen(reinterpret_cast<char*>(mmf_ptr));
  char* text = reinterpret_cast<char*>(mmf_ptr);
  while(true) {
    std::string new_str;

    for (size_t i = 0; i < size; ++i) {
      if (!is_vowel(text[i])) {
        new_str.push_back(text[i]);
      }
    }
    
    std::cout << new_str.c_str() << std::endl;

  }
}
