file(GLOB_RECURSE SRCS "src/*.cpp")

# TODO Find a name
add_library(unnamed STATIC ${SRCS})
set_target_properties(unnamed PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)
target_include_directories(unnamed PUBLIC include)
