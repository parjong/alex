return() # TODO ENABLE THIS PROJECT

file(GLOB_RECURSE TESTS "src/*.test.cpp")

add_library(stdex-contrib INTERFACE)
target_include_directories(stdex-contrib INTERFACE include)

nn_find_package(GTest QUIET)

if(NOT GTest_FOUND)
  return()
endif(NOT GTest_FOUND)

add_executable(stdex-contrib-test ${TESTS})
target_link_libraries(stdex-contrib-test stdex-contrib)
target_link_libraries(stdex-contrib-test gtest_main)

add_test(stdex-contrib-test stdex-contrib-test)
