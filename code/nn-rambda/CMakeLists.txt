return() # TODO ENABLE THIS PROJECT

file(GLOB_RECURSE TESTS "src/*.test.cpp")

add_library(rambda INTERFACE)
target_include_directories(rambda INTERFACE include)

nn_find_package(GTest QUIET)

if(NOT GTest_FOUND)
  return()
endif(NOT GTest_FOUND)

add_executable(rambda-test ${TESTS})
set_target_properties(rambda-test PROPERTIES CXX_STANDARD 14)
target_link_libraries(rambda-test rambda)
target_link_libraries(rambda-test gtest_main)
add_test(rambda-test rambda-test)
