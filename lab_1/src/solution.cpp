#include "../include/solution.hpp"

#define BUFFER_SIZE 4096

void solution() {
  std::pair<int, int> files_desc;
  std::pair<int, int> pipe1_desc;
  std::pair<int, int> pipe2_desc;

  pid_t pid1 = -1;
  pid_t pid2 = -1;

  try {
    open_files(files_desc);

    open_pipe(pipe1_desc);
    open_pipe(pipe2_desc);

    create_process(pid1, pid2);

    if (pid1 != 0 && pid2 != 0) {
      input_handler(pipe1_desc.second, pipe2_desc.second);
    
    } else if (pid1 == 0) {
      second_process_handler(pipe1_desc.first, files_desc.first);

    } else if (pid2 == 0 && pid1 != 0) {
      second_process_handler(pipe2_desc.first, files_desc.second);
    }

  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return;
  }
}

void open_files(std::pair<int, int>& files_descs) {
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

void open_pipe(std::pair<int, int>& pipe_descs) {
  int descs[2]{-1, -1};
  int pipe_status = pipe(descs);

  if (pipe_status < 0) {
    throw std::runtime_error("Pipe create error!");
  }

  pipe_descs.first = descs[0];
  pipe_descs.second = descs[1];
}

Pipes string_filter() noexcept {
  int filter_flag = rand() % 101;

  if (filter_flag <= 80) {
    return FIRST;
  }

  return SECOND;
}

void input_handler(int pipe1_write, int pipe2_write) noexcept {
  while (true) {
    std::cout << "Enter string: ";
    char buf[BUFFER_SIZE];
    std::cin.getline(buf, BUFFER_SIZE);

    if (strlen(buf) > BUFFER_SIZE) {
      std::cerr << "Length out of buffer. Buffer size: " << BUFFER_SIZE << " characters" << std::endl;
      continue;
    }

    Pipes filter_code = string_filter();

    switch(filter_code) {
      case FIRST:
        write(pipe1_write, buf, BUFFER_SIZE);
        break;

      case SECOND:
        write(pipe2_write, buf, BUFFER_SIZE);
        break;
    }
  }
}

void first_process_handler(int pipe1_read, int file1_desc) {
  int flag1 = dup2(pipe1_read, STDIN_FILENO);
  int flag2 = dup2(file1_desc, STDOUT_FILENO);

  if (flag1 == -1 || flag2 == -1) {
    throw std::runtime_error("lol");
  }

  int status = execl("/home/kirill/Desktop/study/MAI_OS/lab_1/build/lab1_main_first", "/home/kirill/Desktop/study/MAI_OS/lab_1/build/lab1_main_first", NULL);
  if (status < 0) {
    throw std::runtime_error("lol");
  }
}

void second_process_handler(int pipe2_read, int file2_desc) {
  int flag1 = dup2(pipe2_read, STDIN_FILENO);
  int flag2 = dup2(file2_desc, STDOUT_FILENO);

  if (flag1 == -1 || flag2 == -1) {
    throw std::runtime_error("lol");
  }

  int status = execl("/home/kirill/Desktop/study/MAI_OS/lab_1/build/lab1_main_second", "/home/kirill/Desktop/study/MAI_OS/lab_1/build/lab1_main_second", NULL);
  if (status < 0) {
    throw std::runtime_error("lol");
  }  
}

void create_process(int& pid1, int& pid2) {
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
