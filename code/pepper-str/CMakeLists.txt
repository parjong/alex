add_library(pepper-str INTERFACE)
target_include_directories(pepper-str INTERFACE include)

add_library(pepper::str ALIAS pepper-str)

alex_find_package(GoogleTest EXACT 1.8.0 REQUIRED)
find_package(Threads REQUIRED)

# TODO Implement GoogleTest_AddTest helper
add_executable(pepper-str-test test.cpp)
add_test(pepper-str-test pepper-str-test)
target_include_directories(pepper-str-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(pepper-str-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(pepper-str-test pepper::str)
target_link_libraries(pepper-str-test Threads::Threads)
