cmake_minimum_required(VERSION 3.6)
project(System-Programming-Weather)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp pongdang.txt)
add_executable(System-Programming-Weather ${SOURCE_FILES})