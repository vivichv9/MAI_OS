cmake_minimum_required(VERSION 3.20)

project(lab5-7)

find_package(wrap_zmq)

add_executable(${PROJECT_NAME}_exe ClientProgramm.cpp)
target_link_options(${PROJECT_NAME}_exe PRIVATE "-Wall")
set_target_properties(${PROJECT_NAME}_exe PROPERTIES
        CXX_STANDART 20
        CXX_STANDART_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}_exe zmq)

add_executable(server ServerProgramm.cpp)
set_target_properties(server PROPERTIES
        CXX_STANDART 20
        CXX_STANDART_REQUIRED ON)
target_link_libraries(server zmq)