add_executable(MissingInteger MissingInteger.cpp)
target_link_libraries(MissingInteger gtest_main gtest pthread)

add_executable(MaxCounters MaxCounters.cpp)
target_link_libraries(MaxCounters gtest_main gtest pthread)

add_executable(PermCheck PermCheck.cpp)
target_link_libraries(PermCheck gtest_main gtest pthread)

add_executable(FrogRiverOne FrogRiverOne.cpp)
target_link_libraries(FrogRiverOne gtest_main gtest pthread)

