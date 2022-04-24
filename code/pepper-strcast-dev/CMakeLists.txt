add_library(pepper-strcast-dev src/strcast.cpp)
target_include_directories(pepper-strcast-dev PUBLIC include)

add_library(pepper::strcast ALIAS pepper-strcast-dev)

alex_find_package(GoogleTest EXACT 1.8.0 REQUIRED)
find_package(Threads REQUIRED)

# TODO Implement GoogleTest_AddTest helper
add_executable(pepper-strcast-dev-test src/strcast.test.cpp)
add_test(pepper-strcast-dev-test pepper-strcast-dev-test)
target_include_directories(pepper-strcast-dev-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(pepper-strcast-dev-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(pepper-strcast-dev-test pepper::strcast)
target_link_libraries(pepper-strcast-dev-test Threads::Threads)
