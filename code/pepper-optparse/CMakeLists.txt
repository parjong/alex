# TODO Enable this
return()

cmake_minimum_required (VERSION 2.8.8)

enable_testing()

add_subdirectory (/usr/src/gtest gtest)

include_directories (. /home/parjong/.pepper/packages/pepper-logging/0.0.0/include /home/parjong/.pepper/packages/pepper-stream/0.0.0/include)
link_directories (/home/parjong/.pepper/packages/pepper-logging/0.0.0/lib /home/parjong/.pepper/packages/pepper-stream/0.0.0/lib)
project (pepper-optparse)

add_definitions (-std=c++11)

add_library (pepper-optparse pepper/optparse/parser.cpp)

target_link_libraries (pepper-optparse pepper-logging pepper-stream log4cxx boost_system boost_filesystem)

install (TARGETS pepper-optparse DESTINATION lib)
install (FILES pepper/optparse/opt/base.hpp DESTINATION include/pepper/optparse/opt)
install (FILES pepper/optparse/opt/required.hpp DESTINATION include/pepper/optparse/opt)
install (FILES pepper/optparse/parser.hpp DESTINATION include/pepper/optparse)

add_executable (test-pepper-optparse pepper/optparse/optparse.test.cpp)

target_link_libraries (test-pepper-optparse gtest gtest_main pthread)
target_link_libraries (test-pepper-optparse pepper-optparse)

add_test (test-pepper-optparse test-pepper-optparse)
