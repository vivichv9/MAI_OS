#ifndef PROCESS_HPP_INCLUDED
#define PROCESS_HPP_INCLUDED

#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <semaphore.h>
#include <memory>
#include <solution.h>


namespace lab3 {

void process_handler(void* mmf_ptr, sem_t* sem, sem_t* full, sem_t* empty);

bool is_vowel(char e) noexcept;

std::string delete_vowels(char* text);

} // namespace lab3 

#endif