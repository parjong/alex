add_library(pepper-benchmark INTERFACE)
target_include_directories(pepper-benchmark INTERFACE include)

add_executable(pepper-benchmark-example example.cpp)
set_target_properties(pepper-benchmark-example PROPERTIES OUTPUT_NAME measure)
target_link_libraries(pepper-benchmark-example pepper-benchmark)
