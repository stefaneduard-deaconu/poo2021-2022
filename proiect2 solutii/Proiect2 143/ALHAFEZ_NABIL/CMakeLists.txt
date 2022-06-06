cmake_minimum_required(VERSION 3.21)
project(proiectul_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        proiectul_2
        main.cpp
        util/IoBase.h
        util/IoBase.cpp
        util/functions.h
        util/functions.cpp
        util/virus_base.h
        util/virus_rootkit.h util/virus_keylogger.h util/ransomware_virus.h util/computer.h util/firma.h util/virus_kernel_keylogger.h util/enumerable.h)
