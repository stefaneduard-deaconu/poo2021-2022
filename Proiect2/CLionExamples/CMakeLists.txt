cmake_minimum_required(VERSION 3.21)
project(project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(project2 main.cpp scripts/sample.h scripts/sample.cpp gui_codes/main.cpp gui_codes/main.h multithreading_codes/main.cpp multithreading_codes/main.h)
