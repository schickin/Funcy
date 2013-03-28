cmake_minimum_required(VERSION 2.6)

project (Funcy)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++0x -g -O3")

find_library (PTHREAD_LIB pthread)

set (FUNCY_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory (tst)
