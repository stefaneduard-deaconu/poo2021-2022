cmake_minimum_required(VERSION 3.22)
project(colocviu)

set(CMAKE_CXX_STANDARD 14)

add_executable(colocviu main.cpp Malware.h IoBase.h Computer.h CrudMenu.h)
