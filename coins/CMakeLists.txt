cmake_minimum_required(VERSION 3.16.3)

set (CMAKE_CXX_STANDART 17)

project (coins) 

set (SOURCE_EXE main.cpp)

set (SOURCE_LIB coins.cpp)

add_library(coins STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main coins)