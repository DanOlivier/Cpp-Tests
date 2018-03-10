cmake_minimum_required(VERSION 3.7)

INCLUDE(FindPkgConfig)
#pkg_check_modules(GMOCK REQUIRED gtest>=1.7.0)
#include_directories(${GTEST_INCLUDE_DIRS})

#enable_testing()
find_package(GTest REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_subdirectory(01-Iterations)
add_subdirectory(02-Arrays)
add_subdirectory(03-Time-Complexity)
add_subdirectory(04-Counting-Elements)
add_subdirectory(05-Prefix-Sums)
add_subdirectory(06-Sorting)
add_subdirectory(07-Stacks-and-Queues)
add_subdirectory(08-Leader)
add_subdirectory(09-Maximum-slice-problem)
add_subdirectory(10-Prime-and-composite-numbers)

add_subdirectory(Various)
