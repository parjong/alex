set(FlatBuffers_Library_SRCS
  ${FlatbuffersSource_DIR}/src/code_generators.cpp
  ${FlatbuffersSource_DIR}/src/idl_parser.cpp
  ${FlatbuffersSource_DIR}/src/idl_gen_text.cpp
  ${FlatbuffersSource_DIR}/src/reflection.cpp
  ${FlatbuffersSource_DIR}/src/util.cpp
)

add_library(flatbuffers STATIC ${FlatBuffers_Library_SRCS})
set_target_properties(flatbuffers PROPERTIES
                      POSITION_INDEPENDENT_CODE ON
                      CXX_STANDARD 11)
target_include_directories(flatbuffers PUBLIC ${FlatbuffersSource_DIR}/include)
