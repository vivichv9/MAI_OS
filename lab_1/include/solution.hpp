#pragma once

#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <utility>
#include "../enums/Pipes.hpp"

void solution();

void open_files(std::pair<int, int>& files_desc);

void open_pipe(std::pair<int, int>& pipe_desc);

Pipes string_filter() noexcept;

void input_handler(int pipe1_write, int pipe2_write) noexcept;

void first_process_handler(int pipe1_read, int file1_desc) noexcept;

void second_process_handler(int pipe2_read, int file2_desc) noexcept;

void create_process(int& pid1, int& pid2);

