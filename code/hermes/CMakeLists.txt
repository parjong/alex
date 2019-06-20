set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SRCS "src/*.cpp")

add_library(hermes STATIC ${SRCS})
set_property(TARGET hermes PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(hermes PUBLIC include)

add_executable(hermes-test sample.cpp)
target_link_libraries(hermes-test hermes)

add_test(hermes-test hermes-test)
