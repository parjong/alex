add_library(lapse INTERFACE)
target_include_directories(lapse INTERFACE include)

add_executable(lapse-test examples.cpp)
target_link_libraries(lapse-test PRIVATE lapse)
add_test(lapse-test lapse-test)
