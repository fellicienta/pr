cmake_minimum_required (VERSION 3.10)

project(boost-test)

find_package(Boost COMPONENTS program_options REQUIRED) 

include_directories(${Boost_INCLUDE_DIRS}) 
add_executable(boost-test main.cpp)
target_link_libraries(boost-test ${Boost_LIBRARIES})


