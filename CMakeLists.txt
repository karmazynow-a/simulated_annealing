cmake_minimum_required(VERSION 3.0)
project(SimulatedAnnealing)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimulatedAnnealing main.cpp Board.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g -pedantic -pedantic-errors -Wextra")