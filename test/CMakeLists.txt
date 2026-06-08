add_executable(njr_algebra_core_test core_test.cpp)
target_link_libraries(njr_algebra_core_test PRIVATE njr::algebra_core GTest::gtest_main)
gtest_discover_tests(njr_algebra_core_test TEST_PREFIX "njr_algebra_core.")
