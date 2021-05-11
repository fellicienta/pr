cmake_minimum_required(VERSION 3.10)

project (RNG) 

find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

set (SOURCE_EXE main.cpp lib.cpp)

add_executable(main ${SOURCE_EXE})

target_link_libraries(main gtest gtest_main gmock pthread)

set_target_properties(main PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF)

gtest_discover_tests(main)