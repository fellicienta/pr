cmake_minimum_required(VERSION 3.16.3)
set (CMAKE_CXX_STANDART 17)

project(str-changer)

set(PROJECT_NAME "str-changer")

set(SOURCES function.cpp)

set(TEST_SOURCES ${SOURCES} Test.cpp)

add_executable(test-${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(test-${PROJECT_NAME} GTest::GTest GTest::Main)

gtest_discover_tests(test-${PROJECT_NAME}))