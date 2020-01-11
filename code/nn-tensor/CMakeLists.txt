return() # TODO ENABLE THIS PROJECT

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE TESTS "src/*.test.cpp")

list(REMOVE_ITEM SOURCES ${TESTS})

add_library(tensor ${SOURCES})
set_target_properties(tensor PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_options(tensor PRIVATE -Werror -Wall)
target_include_directories(tensor PUBLIC include)

nn_find_package(GTest QUIET)

if(NOT GTest_FOUND)
  return()
endif(NOT GTest_FOUND)

add_executable(tensor-test ${TESTS})
set_target_properties(tensor-test PROPERTIES CXX_STANDARD 14)
target_link_libraries(tensor-test tensor)
target_link_libraries(tensor-test gtest_main)
add_test(tensor-test tensor-test)
