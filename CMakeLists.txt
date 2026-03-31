cmake_minimum_required(VERSION 3.10)
project(problem_096)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

add_executable(code solution.cpp)
