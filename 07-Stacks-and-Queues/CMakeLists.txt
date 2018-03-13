add_executable(Nesting Nesting.cpp)
target_link_libraries(Nesting gtest_main gtest pthread)

add_executable(Fish Fish.cpp)
target_link_libraries(Fish gtest_main gtest pthread)

add_executable(Brackets Brackets.cpp)
target_link_libraries(Brackets gtest_main gtest pthread)

