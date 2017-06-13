cmake_minimum_required(VERSION 3.7)
project(algorithms)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)
set(SOURCE_FILES src/*.cpp)
add_executable(reverselinkedlist src/reverse_linked_list.cpp)
add_executable(singly_linked_list_test test/singly_linked_list_test.cpp)