cmake_minimum_required(VERSION 3.10)
project(SortingAlgorithms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror -O3")

include_directories(.)

add_executable(SortingAlgorithms
        main.cpp
        sorting.hpp
        sorting.tpp)
