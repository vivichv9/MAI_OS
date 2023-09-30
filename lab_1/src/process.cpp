#include "../include/process.hpp"

#define BUFFER_SIZE 4096

void process_handler() {
  char* buf = new char[BUFFER_SIZE];

  while(true) {
    read(STDIN_FILENO, buf, BUFFER_SIZE);
    std::cout << buf << std::endl;
  }

  delete[] buf;
}
