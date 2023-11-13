#ifndef SOLUTION_HPP_INCLUDED 
#define SOLUTION_HPP_INCLUDED

#include "Pipes.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <utility>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <semaphore.h>

namespace lab3 {

#define BUFFER 4096
#define N 1

void solution();

void open_files(std::pair<int, int>& files_desc);

void shm_files_open(void*& shm_file, int& desc);

sem_t* create_semaphore(const char* sem_name, size_t count);

Pipes string_filter() noexcept;

void input_handler(void* shm_file, sem_t* sem, sem_t* empty, sem_t* full);

void first_process_handler(int mmf1, int file1_desc, const char* name);

void second_process_handler(int mmf2, int file2_desc, const char* name);

void create_process(int& pid1, int& pid2);
  
} // namespace lab3

#endif