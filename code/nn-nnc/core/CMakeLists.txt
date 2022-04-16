file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE TESTS "src/*.test.cpp")
list(REMOVE_ITEM SOURCES ${TESTS})

add_library(nnc-core STATIC ${SOURCES})
target_include_directories(nnc-core PUBLIC include)

nn_find_package(GTest QUIET)

if(NOT GTest_FOUND)
  return()
endif(NOT GTest_FOUND)

add_executable(nnc-core-test ${TESTS})
target_link_libraries(nnc-core-test nnc-core)
target_link_libraries(nnc-core-test gtest_main)
add_test(nnc-core-test nnc-core-test)
