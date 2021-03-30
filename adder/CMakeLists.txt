cmake_minimum_required (VERSION 3.20)

project(adder)

set(SOURCE_EXE main.cpp)
set(SOURCE_LIB adder.cpp)

add_library(adder STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main adder)
