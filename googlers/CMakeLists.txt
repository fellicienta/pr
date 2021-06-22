cmake_minimum_required(VERSION 3.10)

project (googlers) 

find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

set (SOURCE_EXE Test.cpp lib.cpp)

add_executable(Test ${SOURCE_EXE})

target_link_libraries(Test gtest gtest_main gmock pthread)

set_target_properties(Test PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF)

gtest_discover_tests(Test)