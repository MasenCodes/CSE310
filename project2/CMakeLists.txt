cmake_minimum_required(VERSION 2.8)
project(project2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 14)

add_executable(storm storm.cpp)
