cmake_minimum_required(VERSION 2.8)
project(CSE310)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD 14)

add_executable(main.cpp main.cpp) # add more of these as needed to compile more code
add_executable(encode.cpp encode.cpp)

