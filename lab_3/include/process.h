#ifndef PROCESS_HPP_INCLUDED
#define PROCESS_HPP_INCLUDED

#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fcntl.h>

namespace lab3 {

  void process_handler(void* mmf_ptr);

} // namespace lab3 

#endif