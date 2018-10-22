cmake_minimum_required(VERSION 3.10)
project(SortingAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -O3")

set(HDR_FILES CountingSort.hpp MergeSort.hpp QuickSort.hpp timeit.hpp vector_helpers.hpp)

add_executable(SortingAlgorithms main.cpp ${HDR_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(SortingAlgorithms Threads::Threads)
