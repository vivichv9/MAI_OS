#include "../include/solution.hpp"

#define BUFFER_SIZE 512

void solution() {
  const std::pair<int, int> files_desc = open_files();

  const std::pair<int, int> pipe1_desc = open_pipe();
  const std::pair<int, int> pipe2_desc = open_pipe();

  pid_t pid1 = fork();
  pid_t pid2 = -1;

  if (pid1 > 0) {
    pid2 = fork();

    if (pid2 == -1) {
      throw new std::runtime_error("process 1 create error");
    }  

  } else if (pid1 == -1) {
    throw new std::runtime_error("process 2 create error");
  }

  if (pid1 != 0 && pid2 != 0) {
    input_handler(pipe1_desc.second, pipe2_desc.second);
  
  } else if (pid1 == 0) {
    first_process_handler(pipe1_desc.first, files_desc.first);

  } else if (pid2 == 0 && pid1 != 0) {
    second_process_handler(pipe2_desc.first, files_desc.second);
  }
}

std::pair<int, int> open_files() {
  std::string file_name_1;
  std::string file_name_2;

  std::cout << "Please enter first file name: ";
  std::cin >> file_name_1;
  std::cout << "Please enter second file name: ";
  std::cin >> file_name_2;

  int f1_desc = open(file_name_1.c_str(), O_WRONLY | O_APPEND, 0666);
  int f2_desc = open(file_name_2.c_str(), O_WRONLY | O_APPEND, 0666);

  std::pair<int, int> files_desc{f1_desc, f2_desc};

  if (files_desc.first < 0) {
    throw new std::runtime_error("Error with open file: " + file_name_1);
  }

  if (files_desc.second < 0) {
    throw new std::runtime_error("Error with open file: " + file_name_2);
  }

  return files_desc;
}

std::pair<int, int> open_pipe() {
  int descs[2] = {-1, -1};
  int pipe_status = pipe(descs);

  if (pipe_status < 0) {
    throw new std::runtime_error("Pipe create error!");
  }

  std::pair<int, int> pipe_desc{descs[0], descs[1]};

  return pipe_desc;
}

Pipes string_filter() {
  int filter_flag = 0;
  filter_flag = rand() % 101;

  if (filter_flag <= 80) {
    return FIRST;
  }

  return SECOND;
}

void input_handler(int pipe1_write, int pipe2_write) {
  while (true) {
    std::cout << "Enter string: ";
    std::string buf;
    std::cin >> buf;

    if (buf.size() > BUFFER_SIZE) {
      std::cerr << "Length out of buffer. Buffer size: " << BUFFER_SIZE << " characters" << std::endl;
      continue;
    }

    Pipes filter_code = string_filter();

    switch(filter_code) {
      case FIRST:
        write(pipe1_write, buf.c_str(), BUFFER_SIZE);
        break;

      case SECOND:
        write(pipe2_write, buf.c_str(), BUFFER_SIZE);
        break;
    }
    sleep(1);
  }
  
}

void first_process_handler(int pipe1_read, int file1_desc) {
  dup2(pipe1_read, STDIN_FILENO);
  dup2(file1_desc, STDOUT_FILENO);

  while(true) {
    char buf[BUFFER_SIZE];
    read(pipe1_read, buf, BUFFER_SIZE);
    std::cout << "first: ";
    std::cout << buf << std::endl;
    sleep(1);
  }
}

void second_process_handler(int pipe2_read, int file2_desc) {
  dup2(pipe2_read, STDIN_FILENO);
  dup2(file2_desc, STDOUT_FILENO);

  while(true) {
    char buf[BUFFER_SIZE];
    read(pipe2_read, buf, BUFFER_SIZE);
    std::cout << "second: ";
    std::cout << buf << std::endl; 
    sleep(1);
  }
}
