cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME buffer)
project(${PROJECT_NAME})

find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

set(SOURCES lib.cpp)

set(APP_SOURCES ${SOURCES} main.cpp)
set(TEST_SOURCES ${SOURCES} QTest.cpp)

add_executable(${PROJECT_NAME} ${APP_SOURCES})
add_executable(test-${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(test-${PROJECT_NAME} GTest::gtest GTest::gtest_main gmock)

gtest_discover_tests(test-${PROJECT_NAME})