cmake_minimum_required(VERSION 3.10)

project (looped-list) 

find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

set (SOURCE_EXE Test.cpp)
set (SOURCE_LIB List.cpp)

add_library(List STATIC ${SOURCE_LIB})
add_executable(Test ${SOURCE_EXE})

target_link_libraries(Test List gtest gtest_main gmock pthread)

gtest_discover_tests(Test)