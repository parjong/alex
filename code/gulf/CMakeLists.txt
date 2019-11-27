add_library(gulf INTERFACE)
target_include_directories(gulf INTERFACE include)

alex_find_package(GoogleTest EXACT 1.8.0 REQUIRED)
find_package(Threads REQUIRED)

# TODO Implement GoogleTest_AddTest helper
add_executable(gulf-test gulf.test.cpp)
add_test(gulf-test gulf-test)
target_include_directories(gulf-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(gulf-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(gulf-test Threads::Threads)
target_link_libraries(gulf-test gulf)
