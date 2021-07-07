cmake_minimum_required(VERSION 2.8)

project (libpepper-archive)

###
enable_testing()

###
include_directories (.)

add_definitions (-std=c++11)

list (APPEND LIB_SOURCES pepper/archive/plain/int.cc)
list (APPEND LIB_SOURCES pepper/archive/plain/uint.cc)

add_library (pepper-archive ${LIB_SOURCES}) 

install (TARGETS pepper-archive DESTINATION lib)

install (FILES pepper/archive/archive.h DESTINATION include/pepper/archive) 
install (FILES pepper/archive/archive.decl.h DESTINATION include/pepper/archive) 
install (FILES pepper/archive/util.h DESTINATION include/pepper/archive) 
install (FILES pepper/archive/vector.h DESTINATION include/pepper/archive) 
install (FILES pepper/archive/plain/int.h DESTINATION include/pepper/archive) 
install (FILES pepper/archive/plain/uint.h DESTINATION include/pepper/archive) 

list (APPEND TEST_SOURCES pepper/archive/archive.test.cc)

add_executable (archive-test ${TEST_SOURCES})

target_link_libraries (archive-test pepper-archive)
target_link_libraries (archive-test gtest)
target_link_libraries (archive-test gtest_main)
target_link_libraries (archive-test pthread)

add_test (run-archive-test archive-test)
