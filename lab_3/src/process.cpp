#include "process.h"

bool lab3::is_vowel(char e) noexcept {
  if (e != 'a' &&  e != 'A' && e != 'e' && e != 'E' && 
        e != 'i' && e != 'I' && e != 'o' && e != 'O' && e != 'U' &&
        e != 'u' && e != 'y' && e != 'Y') {

    return false;
  }

  return true;
}

std::string lab3::delete_vowels(char* text, uint32_t size) {
    std::string new_str;

    for (size_t i = 0; i < size; ++i) {
      if (!lab3::is_vowel(text[i])) {
        new_str.push_back(text[i]);
      }
    }

    return new_str; // NRVO
}

void lab3::process_handler(void* mmf_ptr, sem_t* sem, sem_t* full, sem_t* empty) {
  char* text = (char*) malloc(BUFFER);
  uint32_t size = 0;

  while(true) {
    sem_wait(full);
    sem_wait(sem);

    memcpy(&size, mmf_ptr, sizeof(size));
    memcpy(text, (char*) mmf_ptr + sizeof(size), size);

    sem_post(sem);
    sem_post(empty);

    std::cout << lab3::delete_vowels(text, size).c_str() << std::endl;
  }
}
