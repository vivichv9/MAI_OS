  #include "solution.h"

  void lab3::solution() {
    std::pair<int, int> files_desc;

    void* shm_file = nullptr;
    int shm_desc = 0;

    std::string mmf_name = "lab3_mmf_1";
    const char* sem_name = "lab3_semaphore_1";
    const char* isempty_sem_name = "lab3_is_empty_1";
    const char* isfull_sem_name = "lab3_is_full_1";

    void* shm_file_2 = nullptr;
    int shm_desc_2 = 0;

    std::string mmf_name_2 = "lab3_mmf_2";
    const char* sem_name_2 = "lab3_semaphore_2";
    const char* isempty_sem_name_2 = "lab3_is_empty_2";
    const char* isfull_sem_name_2 = "lab3_is_full_2";

    pid_t pid1 = -1;
    pid_t pid2 = -1;

    try {
      lab3::open_files(files_desc);

      lab3::shm_file_open(mmf_name, shm_file, shm_desc);
      lab3::shm_file_open(mmf_name_2, shm_file_2, shm_desc_2);
    
      auto sem = lab3::create_semaphore(sem_name, 1);
      auto empty = lab3::create_semaphore(isempty_sem_name, N);
      auto full = lab3::create_semaphore(isfull_sem_name, 0);

      auto sem_2 = lab3::create_semaphore(sem_name_2, 1);
      auto empty_2 = lab3::create_semaphore(isempty_sem_name_2, N);
      auto full_2 = lab3::create_semaphore(isfull_sem_name_2, 0);

      lab3::create_process(pid1, pid2);

      if (pid1 != 0 && pid2 != 0) {
        lab3::input_handler({shm_file, shm_file_2}, {sem, sem_2}, {empty, empty_2}, {full, full_2});
      
      } else if (pid1 == 0) {
        lab3::first_process_handler(mmf_name, files_desc.first, sem_name, isempty_sem_name, isfull_sem_name);

      } else if (pid2 == 0 && pid1 != 0) {
        lab3::second_process_handler(mmf_name_2, files_desc.second, sem_name_2, isempty_sem_name_2, isfull_sem_name_2);
      }

    } catch (std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
      throw;
    }
  }

  void lab3::open_files(std::pair<int, int>& files_descs) {
    std::string file_name_1;
    std::string file_name_2;

    std::cout << "Please enter first file name: ";
    std::cin >> file_name_1;
    std::cout << "Please enter second file name: ";
    std::cin >> file_name_2;

    file_name_1 = "/home/kirill/Desktop/study/MAI_OS/lab_3/files/a.txt";
    file_name_2 = "/home/kirill/Desktop/study/MAI_OS/lab_3/files/b.txt";

    int f1_desc = open(file_name_1.c_str(), O_RDWR | O_APPEND, 0777);
    int f2_desc = open(file_name_2.c_str(), O_RDWR | O_APPEND, 0777);

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

  sem_t* lab3::create_semaphore(const char* sem_name, size_t count) {
    sem_t* s = sem_open(sem_name, O_CREAT | O_RDWR, 0666, count);

    if (s == SEM_FAILED) {
      throw std::runtime_error("Create semaphore error");
    }
    
    return s;
  }

  void lab3::shm_file_open(std::string name, void*& shm_file, int& desc) {
    int mmf = shm_open(name.c_str(), O_CREAT | O_RDWR, 0666);

    if (mmf < 0) {
      throw std::runtime_error("Error with open mmf: " + name);
    }

    desc = mmf;

    int flag = ftruncate(mmf, BUFFER);

    if (flag < 0) {
      throw std::runtime_error("Error fallocate space");
    }

    void* mmf_ptr = mmap(nullptr, BUFFER, PROT_READ | PROT_WRITE, MAP_SHARED, mmf, 0);

    if (mmf_ptr == MAP_FAILED) {
      throw std::runtime_error("Error with memory mapping with file: " + name);
    }

    shm_file = mmf_ptr;
  }

  Pipes lab3::string_filter() noexcept {
    int filter_flag = rand() % 101;

    if (filter_flag <= 80) {
      return Pipes::FIRST;
    }

    return Pipes::SECOND;
  }

  void lab3::input_handler(std::pair<void*, void*>&& shm_files, std::pair<sem_t*, sem_t*>&& sem, std::pair<sem_t*, sem_t*>&& empty, std::pair<sem_t*, sem_t*>&& full) {
    while (true) {
      std::string buf;
      std::cout << "Enter string: (ctrl + c to exit)" << std::endl;
      std::cin >> buf;

      uint32_t size = buf.size();

      Pipes filter_code = string_filter();
      switch(filter_code) {
        case FIRST:
          sem_wait(empty.first);
          sem_wait(sem.first);
          
          memcpy(shm_files.first, &size, sizeof(size));
          memcpy(static_cast<char*>(shm_files.first) + sizeof(size), buf.c_str(), buf.size());

          sem_post(sem.first);
          sem_post(full.first);
          break; 

        case SECOND:
          sem_wait(empty.second);
          sem_wait(sem.second);

          memcpy(shm_files.second, &size, sizeof(size));
          memcpy(static_cast<char*>(shm_files.second) + sizeof(size), buf.c_str(), buf.size());

          sem_post(sem.second);
          sem_post(full.second);        
          break;
      }
    }
  }

  void lab3::first_process_handler(std::string mmf_name, int file1_desc, const char* sem_name, const char* empty_sem_name, const char* full_sem_name) {
    int flag2 = dup2(file1_desc, STDOUT_FILENO);

    if (flag2 == -1) {
      throw std::runtime_error("error dup2 first_process_handler");
    }

    int status = execl(
      "/home/kirill/Desktop/study/MAI_OS/lab_3/build/lab3_main_first",
      "/home/kirill/Desktop/study/MAI_OS/lab_3/build/lab3_main_first",
      mmf_name.c_str(),
      sem_name,
      empty_sem_name,
      full_sem_name,
      NULL);

    if (status < 0) {
      throw std::runtime_error("error execl first_process_handler");
    }
  }

  void lab3::second_process_handler(std::string mmf_name, int file2_desc, const char* sem_name, const char* empty_sem_name, const char* full_sem_name) {
    int flag2 = dup2(file2_desc, STDOUT_FILENO);

    if (flag2 == -1) {
      throw std::runtime_error("error dup2 second_process_handler");
    }

    int status = execl(
      "/home/kirill/Desktop/study/MAI_OS/lab_3/build/lab3_main_second", 
      "/home/kirill/Desktop/study/MAI_OS/lab_3/build/lab3_main_second", 
      mmf_name.c_str(), 
      sem_name, 
      empty_sem_name,
      full_sem_name,
      NULL);

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
