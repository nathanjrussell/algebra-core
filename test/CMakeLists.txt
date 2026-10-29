add_executable(algebra_core_test core_test.cpp)
target_link_libraries(algebra_core_test PRIVATE algebra::core GTest::gtest_main)
gtest_discover_tests(algebra_core_test TEST_PREFIX "algebra_core.")
