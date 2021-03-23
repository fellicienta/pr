cmake_minimum_required(VERSION 3.16.3)

set (CMAKE_CXX_STANDART 17)

project (str_changer) 

#find_package(GTest REQUIRED)
add_subdirectory(googletest)
include(GoogleTest)

enable_testing()

set (SOURCE_EXE Test.cpp)
set (SOURCE_LIB function.cpp)

add_library(function STATIC ${SOURCE_LIB})
add_executable(main ${SOURCE_EXE})

target_link_libraries(main function gtest gtest_main gmock)


gtest_discover_tests(main)