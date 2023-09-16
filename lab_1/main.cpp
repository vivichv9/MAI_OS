#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <iostream>

int main() {
  std::string file_name_1;
  std::string file_name_2;

  std::cout << "Please enter first file name: ";
  std::cin >> file_name_1;
  std::cout << "Please enter second file name: ";
  std::cin >> file_name_2;

  if (file_name_1 == "" || file_name_2 == "") {
    throw new std::invalid_argument("Uncorrect file name!");
  }

  int pipe_desc_1[2] = {-1, -1};
  int pipe_desc_2[2] = {-1, -1};

  int pipe_code1 = pipe(pipe_desc_1);
  int pipe_code2 = pipe(pipe_desc_2);

  if (pipe_code1 < 0 || pipe_code2 < 0) {
    std::cerr << "Error with open pipe" << std::endl;
    return -1;
  }

  int file_desc_1 = open("files/file1.txt", O_WRONLY | O_APPEND, 0666);
  int file_desc_2 = open("files/file2.txt", O_WRONLY | O_APPEND, 0666);

  if (file_desc_1 <= 0 || file_desc_2 <= 0) {
    std::cerr << "File open error" << std::endl;
    return -1;
  }

  pid_t pid1 = fork();
  pid_t pid2 = -1;

  if (pid1 > 0) {
    pid2 = fork();

    if (pid2 == -1) {
      std::cerr << "Create process 1 error" << std::endl;
      return -1;
    }  

  } else if (pid1 == -1) {
    std::cerr << "Create process 2 error" << std::endl;
    return -1;
  }

  if (pid1 != 0 && pid2 != 0) {
    int32_t filter_flag = 0;

    do {
      std::cout << "Enter string: ";
      char buf[512];
      std::cin.getline(buf, 512);
      
      filter_flag = rand();

      if (filter_flag <= RAND_MAX / 2) {
        write(pipe_desc_1[1], buf, 512);

      } else {
        write(pipe_desc_2[1], buf, 512);
      }
      sleep(1);

    } while (true);

    // std::cout << "Enter string: ";
    // char buf[512];
    // while (std::cin.getline(buf, 512)) {
    //   int32_t filter_flag = 0;
    //   filter_flag = rand();

    //   if (filter_flag <= RAND_MAX / 2) {
    //     write(pipe_desc_1[1], buf, 512);

    //   } else {
    //     write(pipe_desc_2[1], buf, 512);
    //   }
    //   sleep(1);
    //   std::cout << "Enter string: ";
    // }

  } else if (pid1 == 0) {
    dup2(pipe_desc_1[0], STDIN_FILENO);
    dup2(file_desc_1, STDOUT_FILENO);

    while(true) {
      char buf[512];
      read(pipe_desc_1[0], buf, 512);
      std::cout << "first: ";
      std::cout << buf << std::endl;
      sleep(1);
    }

  } else if (pid2 == 0 && pid1 != 0) {
    dup2(pipe_desc_2[0], STDIN_FILENO);
    dup2(file_desc_2, STDOUT_FILENO);

    while(true) {
      char buf[512];
      read(pipe_desc_2[0], buf, 512);
      std::cout << "second: ";
      std::cout << buf << std::endl; 
      sleep(1);
    }
  }
}  