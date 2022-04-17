cmake_minimum_required(VERSION 3.21)

project(POO)
set(CMAKE_CXX_STANDARD 17)

set(UTIL_SOURCE_FILES util/IoBase.h util/IoBase.cpp util/functions.h util/functions.cpp)

# Ctrl+/ pentru a comenta/decomenta linii
add_executable(pas1 pas1.cpp ${UTIL_SOURCE_FILES})  # TODO aici includem inclusiv IoBase si operator>> pentru vector<T>
#add_executable(pas2 pas2.cpp ${UTIL_SOURCE_FILES})
#add_executable(pas3 pas3.cpp ${UTIL_SOURCE_FILES})
#add_executable(pas4 pas4.cpp ${UTIL_SOURCE_FILES})
#add_executable(pas5 pas5.cpp ${UTIL_SOURCE_FILES})
#add_executable(pas6 pas6.cpp ${UTIL_SOURCE_FILES})
#add_executable(pas7 pas7.cpp ${UTIL_SOURCE_FILES})
