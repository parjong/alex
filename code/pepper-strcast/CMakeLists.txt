add_library(pepper-strcast src/strcast.cpp)
target_include_directories(pepper-strcast PUBLIC include)

add_library(pepper::strcast ALIAS pepper-strcast)

alex_find_package(GoogleTest EXACT 1.8.0 REQUIRED)
find_package(Threads REQUIRED)

# TODO Implement GoogleTest_AddTest helper
add_executable(pepper-strcast-test src/strcast.test.cpp)
add_test(pepper-strcast-test pepper-strcast-test)
target_include_directories(pepper-strcast-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(pepper-strcast-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(pepper-strcast-test pepper::strcast)
target_link_libraries(pepper-strcast-test Threads::Threads)
