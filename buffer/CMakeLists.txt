cmake_minimum_required(VERSION 3.20)

project (buffer) 

#add_subdirectory(googletest)
include(GoogleTest)

enable_testing()

set (SOURCE_EXE QTest.cpp)
set (SOURCE_LIB lib.cpp)

add_library(lib STATIC ${SOURCE_LIB})
add_executable(QTest ${SOURCE_EXE})

target_link_libraries(QTest lib gtest gtest_main gmock)

gtest_discover_tests(QTest)