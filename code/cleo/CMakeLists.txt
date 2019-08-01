file(GLOB_RECURSE LIB_SRCS "src/*.cpp")

add_library(cleo STATIC ${LIB_SRCS})
set_target_properties(cleo PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  CXX_STANDARD 14
)
target_include_directories(cleo PUBLIC include)

add_executable(cleo-sample sample.cpp)
target_link_libraries(cleo-sample PRIVATE cleo)

add_test(cleo-test cleo-sample)
