cmake_minimum_required (VERSION 3.20)

project(boost-test)

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED OFF)  
#set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.71.0 COMPONENTS program_options) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(boost-test main.cpp)
    target_link_libraries(boost-test ${Boost_LIBRARIES})
endif()

