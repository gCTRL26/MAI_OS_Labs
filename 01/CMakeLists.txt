cmake_minimum_required(VERSION 3.20)
project(01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_library(lib src/sys_calls.cpp)
add_library(os_lib src/os.cpp)

target_link_libraries(lib PUBLIC os_lib)

add_executable(main main.cpp)
target_link_libraries(main lib)
add_executable(child src/child.cpp)
configure_file(numbers.txt numbers.txt COPYONLY)