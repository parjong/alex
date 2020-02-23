add_executable(voca-design design.cpp)
target_link_libraries(voca-design PRIVATE fipe)
add_test(voca-design-test voca-design)
