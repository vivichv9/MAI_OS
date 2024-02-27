cmake_minimum_required(VERSION 3.14)

project(kp)

add_subdirectory(third_party/inipp)

# Project lib
add_library(${PROJECT_NAME}_lib
        src/solution.cpp)

target_include_directories(${PROJECT_NAME}_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(${PROJECT_NAME}_lib PUBLIC "-Wall" "-Werror" "-g" "-fsanitize=undefined" "-fsanitize=address")
target_link_options(${PROJECT_NAME}_lib PUBLIC "-fsanitize=undefined" "-fsanitize=address")
set_target_properties(${PROJECT_NAME}_lib PROPERTIES
        CXX_STANDART 20
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME}_lib PUBLIC inipp::inipp)

# Project exe target
add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)