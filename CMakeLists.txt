cmake_minimum_required(VERSION 3.7)

INCLUDE(FindPkgConfig)
#pkg_check_modules(GMOCK REQUIRED gtest>=1.7.0)
#include_directories(${GTEST_INCLUDE_DIRS})

#enable_testing()
find_package(GTest REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_executable(test2 test2.cpp)
target_link_libraries(test2 boost_filesystem boost_system pthread)

add_executable(BinaryGap BinaryGap.cpp)
target_link_libraries(BinaryGap gtest_main gtest)

add_executable(OddOccurrencesInArray OddOccurrencesInArray.cpp)
target_link_libraries(OddOccurrencesInArray gtest_main gtest)

add_executable(CyclicRotation CyclicRotation.cpp)
target_link_libraries(CyclicRotation gtest_main gtest)

add_executable(PermMissingElem PermMissingElem.cpp)
target_link_libraries(PermMissingElem gtest_main gtest)

add_executable(isPermutation isPermutation.cpp)
target_link_libraries(isPermutation gtest_main gtest)

add_executable(PassingCars PassingCars.cpp)
target_link_libraries(PassingCars gtest_main gtest)

add_executable(Brackets Brackets.cpp)
target_link_libraries(Brackets gtest_main gtest)

add_executable(Nesting Nesting.cpp)
target_link_libraries(Nesting gtest_main gtest)

add_executable(Fish Fish.cpp)
target_link_libraries(Fish gtest_main gtest)
target_compile_options(Fish PRIVATE -std=c++1y)

add_executable(NumberSolitaire NumberSolitaire.cpp)
target_link_libraries(NumberSolitaire gtest_main gtest)


add_executable(LongestQuasiConstant LongestQuasiConstant.cpp)
target_link_libraries(LongestQuasiConstant gtest_main gtest)

add_executable(CoinAdjacency CoinAdjacency.cpp)
target_link_libraries(CoinAdjacency gtest_main gtest)
