#include "process.h"
#include <fstream>

int main(int argc, char** argv) {
  std::string mmf_name2 = "second_mmf";
  int mmf2 = shm_open(mmf_name2.c_str(), O_CREAT | O_RDWR, 0666);

  void* mmf2_ptr = mmap(nullptr, BUFFER, PROT_READ | PROT_WRITE, MAP_SHARED, mmf2, 0);
  
  if (mmf2_ptr == MAP_FAILED) {
    throw std::runtime_error("Map failed second process");
  }

  sem_t* sem = sem_open(argv[2], O_CREAT | O_RDWR, 0666, 1);
  sem_t* full = sem_open("is_full", O_CREAT | O_RDWR, 0666, 0);
  sem_t* empty = sem_open("is_empty", O_CREAT | O_RDWR, 0666, 1);

  if (sem == SEM_FAILED || full == SEM_FAILED) {
    throw std::runtime_error("Semaphore failed first process");
  }

  lab3::process_handler(mmf2_ptr, sem, full, empty);
}