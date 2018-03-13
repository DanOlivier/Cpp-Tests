add_executable(MaxProductOfThree MaxProductOfThree.cpp)
target_link_libraries(MaxProductOfThree gtest_main gtest pthread)

add_executable(NumberOfDiscIntersections NumberOfDiscIntersections.cpp)
target_link_libraries(NumberOfDiscIntersections gtest_main gtest pthread)

add_executable(Distinct Distinct.cpp)
target_link_libraries(Distinct gtest_main gtest pthread)

add_executable(Triangle Triangle.cpp)
target_link_libraries(Triangle gtest_main gtest pthread)

