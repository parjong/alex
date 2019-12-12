alex_find_package(GoogleTest EXACT 1.8.0 REQUIRED)
find_package(Threads REQUIRED)

# TODO Implement GoogleTest_AddTest helper
add_executable(memreserve-test memreserve.test.cpp)
add_test(memreserve-test memreserve-test)
target_include_directories(memreserve-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(memreserve-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(memreserve-test Threads::Threads)
target_link_libraries(memreserve-test fipe)
