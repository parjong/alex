file(GLOB_RECURSE SRCS "src/*.cpp")

add_library(cli STATIC ${SRCS})
set_target_properties(cli PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  CXX_STANDARD 14
)
target_include_directories(cli PUBLIC include)
target_link_libraries(cli PUBLIC cleo-core)

add_executable(cli-sample sample.cpp)
set_target_properties(cli-sample PROPERTIES
  # TODO Use C++ 11
  CXX_STANDARD 14
)
target_link_libraries(cli-sample PRIVATE cli)
