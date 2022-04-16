return() # TODO REMOVE THIS PROJECT

cmake_minimum_required(VERSION 2.8)

project (libpepper-tokens)

###
enable_testing()

###
include_directories (.)

add_definitions (-std=c++11 -g)

list (APPEND LIB_SOURCES pepper/tokens/cursor.cc)
list (APPEND LIB_SOURCES pepper/tokens/tokens.cc)
list (APPEND LIB_SOURCES pepper/tokens/scanner.cc)
list (APPEND LIB_SOURCES pepper/tokens/stream/array.cc)

add_library (pepper-tokens ${LIB_SOURCES}) 

install (TARGETS pepper-tokens DESTINATION lib)

install (FILES pepper/tokens/tokens.h DESTINATION include/pepper/tokens) 
install (FILES pepper/tokens/array_tokens.h DESTINATION include/pepper/tokens) 

list (APPEND TEST_SOURCES pepper/tokens/tokens.test.cc)

add_executable (tokens-test ${TEST_SOURCES})

target_link_libraries (tokens-test pepper-tokens)
target_link_libraries (tokens-test gtest)
target_link_libraries (tokens-test gtest_main)
target_link_libraries (tokens-test pthread)

add_test (run-tokens-test tokens-test)

list (APPEND EXPR_SOURCES pepper/tokens/tokens.expr.cc)

add_executable (tokens-expr ${EXPR_SOURCES})

target_link_libraries (tokens-expr pepper-tokens)
