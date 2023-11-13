#include "process.h"

int main(int argc, char** argv) {
  std::string mmf_name1 = "lab3_mmf";

  int mmf1 = shm_open(mmf_name1.c_str(), O_CREAT | O_RDWR, 0666);
  void* mmf1_ptr = mmap(nullptr, BUFFER, PROT_READ | PROT_WRITE, MAP_SHARED, mmf1, 0);

  if (mmf1_ptr == MAP_FAILED) {
    throw std::runtime_error("Map failed first process");
  }

  sem_t* sem = sem_open(argv[2], O_CREAT | O_RDWR, 0666, 1);
  sem_t* full = sem_open("is_full", O_CREAT | O_RDWR, 0666, 0);
  sem_t* empty = sem_open("is_empty", O_CREAT | O_RDWR, 0666, 1);

  if (sem == SEM_FAILED || full == SEM_FAILED) {
    throw std::runtime_error("Semaphore failed first process");
  }

  lab3::process_handler(mmf1_ptr, sem, full, empty);
}