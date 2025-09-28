cmake_minimum_required(VERSION 3.20)
project(01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(parent src/parent.cpp)
add_executable(child src/child.cpp)
configure_file(numbers.txt numbers.txt COPYONLY)