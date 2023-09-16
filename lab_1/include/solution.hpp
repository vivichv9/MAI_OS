#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <utility>
#include "../enums/Pipes.hpp"

void solution();

std::pair<int, int> open_files();

std::pair<int, int> open_pipe();

Pipes string_filter();

void input_handler(int pipe1_write, int pipe2_write);

void first_process_handler(int pipe1_read, int file1_desc);

void second_process_handler(int pipe2_read, int file2_desc);

