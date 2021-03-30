cmake_minimum_required (VERSION 3.20)

project(adder)

set(SOURCE_EXE test.cpp)
set(SOURCE_LIB adder.cpp)

add_library(adder STATIC ${SOURCE_LIB})

add_executable(test ${SOURCE_EXE})

target_link_libraries(test adder)
