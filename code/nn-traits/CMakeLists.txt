return() # TODO ENABLE THIS PROJECT

file(GLOB_RECURSE TESTS "src/*.test.cpp")

add_library(traits INTERFACE)
target_include_directories(traits INTERFACE include)

nn_find_package(GTest QUIET)

if(NOT GTest_FOUND)
  return()
endif(NOT GTest_FOUND)

add_executable(traits-test ${TESTS})
target_link_libraries(traits-test traits)
target_link_libraries(traits-test gtest_main)
add_test(traits-test traits-test)
