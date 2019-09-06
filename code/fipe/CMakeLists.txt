add_library(fipe INTERFACE)
target_include_directories(fipe INTERFACE include)

alex_find_package(GoogleTest EXACT 1.8.0 REQUIRED)
find_package(Threads REQUIRED)

# TODO Implement GoogleTest_AddTest helper
add_executable(fipe-test fipe.test.cpp)
add_test(fipe-test fipe-test)
target_include_directories(fipe-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(fipe-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(fipe-test Threads::Threads)
target_link_libraries(fipe-test fipe)
