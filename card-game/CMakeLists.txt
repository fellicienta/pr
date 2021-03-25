cmake_minimum_required(VERSION 3.16.3)

set (CMAKE_CXX_STANDART 17)

project (card-game) 

set (SOURCE_EXE main.cpp)

set (SOURCE_LIB cards.cpp)

add_library(cards STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main cards)