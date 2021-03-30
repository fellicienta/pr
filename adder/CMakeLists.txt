cmake_minimum_required(VERSION 3.20)

project (adder) 

add_subdirectory(googletest)
include(GoogleTest)

enable_testing()

set (SOURCE_EXE Test.cpp)
set (SOURCE_LIB adder.cpp)

add_library(adder STATIC ${SOURCE_LIB})
add_executable(Test ${SOURCE_EXE})

target_link_libraries(Test adder gtest gtest_main gmock)

gtest_discover_tests(Test)