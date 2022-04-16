return() # TODO ENABLE THIS PROEJCT

file(GLOB_RECURSE TESTS "src/*.test.cpp")

add_library(pepper-contrib INTERFACE)
target_include_directories(pepper-contrib INTERFACE include)

nn_find_package(GTest QUIET)

if(NOT GTest_FOUND)
  return()
endif(NOT GTest_FOUND)

add_executable(pepper-contrib-test ${TESTS})
target_link_libraries(pepper-contrib-test pepper-contrib)
target_link_libraries(pepper-contrib-test gtest_main)
add_test(pepper-contrib-test pepper-contrib-test)
