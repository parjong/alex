file(GLOB_RECURSE SRCS "src/*.cpp")

add_library(hermes STATIC ${SRCS})
set_target_properties(hermes PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  # TODO Use C++ 11
  CXX_STANDARD 14
)
target_include_directories(hermes PUBLIC include)

add_executable(hermes-sample sample.cpp)
set_target_properties(hermes-sample PROPERTIES
  # TODO Use C++ 11
  CXX_STANDARD 14
)
target_link_libraries(hermes-sample PRIVATE hermes)

add_test(
  NAME hermes-test
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/runtest" $<TARGET_FILE:hermes-sample>
)
