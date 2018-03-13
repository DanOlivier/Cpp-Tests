add_executable(Q1 Q1.cpp)
target_link_libraries(Q1 gtest_main gtest)

add_executable(Q2 Q2.cpp)
target_link_libraries(Q2 gtest_main gtest)

add_executable(Q3 Q3.cpp)
target_link_libraries(Q3 gtest_main gtest)

add_executable(Q4 Q4.cpp Q4-tests.cpp)
target_link_libraries(Q4 gtest_main gtest)

add_executable(Q4-1 Q4-1.cpp Q4-tests.cpp)
target_link_libraries(Q4-1 gtest_main gtest)
