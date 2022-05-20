cmake_minimum_required(VERSION 3.21)
project(project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(project2 main.cpp scripts/sample.h scripts/sample.cpp gui/main.cpp gui/main.h "../../Laborator 10/main.cpp")
