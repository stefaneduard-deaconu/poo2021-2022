cmake_minimum_required(VERSION 3.21)

project(POO)
set(CMAKE_CXX_STANDARD 17)

set(UTIL_SOURCE_FILES util/IoBase.h util/IoBase.cpp util/functions.h util/functions.cpp)

# Ctrl+/ pentru a comenta/decomenta linii
#add_executable(main1.cpp ${UTIL_SOURCE_FILES})  # TODO aici includem inclusiv IoBase si operator>> pentru vector<T>
#add_executable(main2.cpp ${UTIL_SOURCE_FILES})
#add_executable(main3.cpp ${UTIL_SOURCE_FILES})
#add_executable(main4.cpp ${UTIL_SOURCE_FILES})
add_executable(main5.cpp ${UTIL_SOURCE_FILES})
