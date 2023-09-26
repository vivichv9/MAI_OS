#include "../include/first_process.hpp"

#define BUFFER_SIZE 4096

void process_handler() {
    while(true) {
    char* buf = new char[BUFFER_SIZE];
    read(STDIN_FILENO, buf, BUFFER_SIZE);
    std::cout << buf << std::endl;
  }
}