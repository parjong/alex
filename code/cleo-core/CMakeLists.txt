file(GLOB_RECURSE LIB_SRCS "src/*.cpp")

add_library(cleo-core STATIC ${LIB_SRCS})
set_target_properties(cleo-core PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(cleo-core PUBLIC include)

file(GLOB_RECURSE TST_SRCS "test/*.cpp")
add_executable(cleo-core-sample ${TST_SRCS} sample.cpp)
target_link_libraries(cleo-core-sample cleo-core)
add_test(cleo-core-test cleo-core-sample)
