cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g -Wall -Werror -O0)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENUM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/enums)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE ENUMS LIST_DIRECTORIES false ${ENUM_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDES LIST_DIRECTORIES false ${INCLUDE_DIR}/*.hpp)

add_library(${CMAKE_PROJECT_NAME}_lib 
            ${SOURCES}
            ${INCLUDES}
            ${ENUMS})

add_executable(${CMAKE_PROJECT_NAME}_main_exe main_files/main.cpp)
add_dependencies(${CMAKE_PROJECT_NAME}_main_exe ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(${CMAKE_PROJECT_NAME}_main_exe ${CMAKE_PROJECT_NAME}_lib)

add_executable(${CMAKE_PROJECT_NAME}_main_first main_files/main_first_process.cpp)
add_dependencies(${CMAKE_PROJECT_NAME}_main_first ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(${CMAKE_PROJECT_NAME}_main_first ${CMAKE_PROJECT_NAME}_lib)

add_executable(${CMAKE_PROJECT_NAME}_main_second main_files/main_second_process.cpp)
add_dependencies(${CMAKE_PROJECT_NAME}_main_second ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(${CMAKE_PROJECT_NAME}_main_second ${CMAKE_PROJECT_NAME}_lib)