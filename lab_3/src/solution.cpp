#include "solution.h"

void lab3::solution() {
  std::pair<int, int> files_desc;
  std::pair<void*, void*> shm_files;

  pid_t pid1 = -1;
  pid_t pid2 = -1;

  try {
    lab3::open_files(files_desc);
    lab3::create_process(pid1, pid2);
    lab3::shm_files_open(shm_files);
    
    if (pid1 != 0 && pid2 != 0) {
      lab3::input_handler(shm_files);
    
    } else if (pid1 == 0) {
      lab3::first_process_handler(shm_files.first, files_desc.first);

    } else if (pid2 == 0 && pid1 != 0) {
      lab3::second_process_handler(shm_files.second, files_desc.second);
    }

  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return;
  }
}

void lab3::open_files(std::pair<int, int>& files_descs) {
  std::string file_name_1;
  std::string file_name_2;

  std::cout << "Please enter first file name: ";
  std::cin >> file_name_1;
  std::cout << "Please enter second file name: ";
  std::cin >> file_name_2;

  int f1_desc = open(file_name_1.c_str(), O_WRONLY | O_APPEND, 0666);
  int f2_desc = open(file_name_2.c_str(), O_WRONLY | O_APPEND, 0666);

  if (f1_desc < 0 && f2_desc < 0) {
    throw std::runtime_error("Error with open files: " + file_name_1 + ", " + file_name_2);
  }

  if (f1_desc < 0) {
    throw std::runtime_error("Error with open file: " + file_name_1);
  }

  if (f2_desc < 0) {
    throw std::runtime_error("Error with open file: " + file_name_2);
  }

  files_descs.first = f1_desc;
  files_descs.second = f2_desc;
}

void lab3::shm_files_open(std::pair<void*, void*>& shm_files) {
  std::string mmf_name1 = "first_mmf";
  std::string mmf_name2 = "second_mmf";

  int mmf1 = shm_open(mmf_name1.c_str(), O_CREAT | O_RDWR, 0666);
  int mmf2 = shm_open(mmf_name2.c_str(), O_CREAT | O_RDWR, 0666);

  if (mmf1 < 0) {
    throw std::runtime_error("Error with open mmf: " + mmf_name1);
  }

  if (mmf2 < 0) {
    throw std::runtime_error("Error with open mmf: " + mmf_name2);
  }

  int flag1 = posix_fallocate(mmf1, 0, BUFFER);
  int flag2 = posix_fallocate(mmf2, 0, BUFFER);

  if (flag1 < 0 || flag2 < 0) {
    throw std::runtime_error("Error fallocate space");
  }

  void* mmf1_ptr = mmap(nullptr, BUFFER, PROT_READ | PROT_WRITE, MAP_SHARED, mmf1, 0);
  void* mmf2_ptr = mmap(nullptr, BUFFER, PROT_READ | PROT_WRITE, MAP_SHARED, mmf2, 0);

  if (mmf1_ptr == MAP_FAILED) {
    throw std::runtime_error("Error with memory mapping with file: " + mmf_name1);
  }

  if (mmf2_ptr == MAP_FAILED) {
    throw std::runtime_error("Error with memory mapping with file: " + mmf_name2);
  }

  shm_files.first = mmf1_ptr;
  shm_files.second = mmf2_ptr;
}

Pipes lab3::string_filter() noexcept {
  int filter_flag = rand() % 101;

  if (filter_flag <= 80) {
    return Pipes::FIRST;
  }

  return Pipes::SECOND;
}

void lab3::input_handler(const std::pair<void*, void*>& shm_files) noexcept {
  std::string buf;

  while (true) {
    getline(std::cin, buf);

    if (buf.size() > BUFFER) {
      std::cerr << "Buffer is overflow, input again!" << std::endl;
      continue;
    }

    std::cerr << "Enter string: (ctrl + c to exit)" << std::endl;
    Pipes filter_code = string_filter();

    switch(filter_code) {
      case FIRST:
        memcpy(shm_files.first, buf.c_str(), buf.size());
        break;

      case SECOND:
        memcpy(shm_files.second, buf.c_str(), buf.size());
        break;
    }
  }
}

void lab3::first_process_handler(void* mmf1, int file1_desc) {
  int flag2 = dup2(file1_desc, STDOUT_FILENO);

  if (flag2 == -1) {
    throw std::runtime_error("error dup2 first_process_handler");
  }

  int status = execl("/home/kirill/Desktop/study/MAI_OS/lab_1/build/lab1_main_first", "/home/kirill/Desktop/study/MAI_OS/lab_1/build/lab1_main_first", mmf1, NULL);
  if (status < 0) {
    throw std::runtime_error("error execl first_process_handler");
  }
}

void lab3::second_process_handler(void* mmf2, int file2_desc) {
  int flag2 = dup2(file2_desc, STDOUT_FILENO);

  if (flag2 == -1) {
    throw std::runtime_error("error dup2 second_process_handler");
  }

  int status = execl("/home/kirill/Desktop/study/MAI_OS/lab_1/build/lab1_main_second", "/home/kirill/Desktop/study/MAI_OS/lab_1/build/lab1_main_second", mmf2, NULL);
  if (status < 0) {
    throw std::runtime_error("error execl second_process_handler");
  }  
}

void lab3::create_process(int& pid1, int& pid2) {
  pid1 = fork();
  pid2 = -1;

  if (pid1 > 0) {
    pid2 = fork();

    if (pid2 == -1) {
      throw std::runtime_error("process 1 create error");
    }  

  } else if (pid1 == -1) {
    throw std::runtime_error("process 2 create error");
  }
}
