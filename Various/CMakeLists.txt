add_executable(test2 test2.cpp)
target_link_libraries(test2 boost_filesystem boost_system pthread)

add_executable(isPermutation isPermutation.cpp)
target_link_libraries(isPermutation gtest_main gtest)

add_executable(NumberSolitaire NumberSolitaire.cpp)
target_link_libraries(NumberSolitaire gtest_main gtest)

add_executable(LongestQuasiConstant LongestQuasiConstant.cpp)
target_link_libraries(LongestQuasiConstant gtest_main gtest)

add_executable(CoinAdjacency CoinAdjacency.cpp)
target_link_libraries(CoinAdjacency gtest_main gtest)
