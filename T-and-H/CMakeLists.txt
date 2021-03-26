cmake_minimum_required(VERSION 3.16.3)

project (T-and-H) 

set (SOURCE_EXE main.cpp)

set (SOURCE_LIB lib.cpp)

add_library(lib STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main lib)