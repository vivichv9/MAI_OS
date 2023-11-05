cmake_minimum_required(VERSION 3.22)

project(lab3)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Project lib
add_library(${PROJECT_NAME}_lib ${SOURCES})

target_include_directories(${PROJECT_NAME}_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_compile_options(${PROJECT_NAME}_lib PUBLIC "-Wall" "-Werror" "-lrt")

set_target_properties(${PROJECT_NAME}_lib PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED ON)

# add main executable target
add_executable(${PROJECT_NAME}_main_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_main_exe ${PROJECT_NAME}_lib)

# add first process executable target
add_executable(${PROJECT_NAME}_main_first main_first_process.cpp)
target_link_libraries(${PROJECT_NAME}_main_first ${PROJECT_NAME}_lib)

# add second process executable target
add_executable(${PROJECT_NAME}_main_second main_second_process.cpp)
target_link_libraries(${PROJECT_NAME}_main_second ${PROJECT_NAME}_lib)

