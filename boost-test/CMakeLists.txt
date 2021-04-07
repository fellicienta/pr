cmake_minimum_required (VERSION 3.10)

project(boost-test)

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED OFF)  
#set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS program_options REQUIRED) 

include_directories(${Boost_INCLUDE_DIRS}) 
add_executable(boost-test main.cpp)
target_link_libraries(boost-test ${Boost_LIBRARIES})


