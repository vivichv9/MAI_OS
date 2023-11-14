#include "process.h"

int main(int argc, char** argv) {
  const char* mmf_name = argv[1];
  const char* sem_name = argv[2];
  const char* isfull_sem_name = argv[4];
  const char* isempty_sem_name = argv[3];

  void* mmf_ptr = nullptr;
  int shm_desc = 0;
  
  lab3::shm_file_open(mmf_name, mmf_ptr, shm_desc);

  sem_t* sem = lab3::create_semaphore(sem_name, 1);
  sem_t* full = lab3::create_semaphore(isfull_sem_name, 0);
  sem_t* empty = lab3::create_semaphore(isempty_sem_name, N);

  lab3::process_handler(mmf_ptr, sem, full, empty);
}