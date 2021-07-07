alex_find_package(GoogleTest EXACT 1.8.0 REQUIRED)
find_package(Threads REQUIRED)

# TODO Implement GoogleTest_AddTest helper
add_executable(eve-test eve.test.cpp)
add_test(eve-test eve-test)
target_include_directories(eve-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(eve-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(eve-test Threads::Threads)
