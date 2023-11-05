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

namespace lab3 {

#define BUFFER 4096

void solution();

void open_files(std::pair<int, int>& files_desc);

void shm_files_open(std::pair<void*, void*>& shm_files_desc);

Pipes string_filter() noexcept;

void input_handler(const std::pair<void*, void*>& shm_files_desc) noexcept;

void first_process_handler(void* mmf1, int file1_desc);

void second_process_handler(void* mmf2, int file2_desc);

void create_process(int& pid1, int& pid2);
  
} // namespace lab3

#endif