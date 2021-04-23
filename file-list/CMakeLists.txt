cmake_minimum_required(VERSION 3.10)

project (string-list) 

find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

set (SOURCE_EXE Test.cpp)

add_executable(Test ${SOURCE_EXE})

target_link_libraries(Test gtest gtest_main gmock pthread)

gtest_discover_tests(Test)