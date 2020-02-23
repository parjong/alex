# Header Generator
add_executable(dla-gen gen.cpp)
target_include_directories(dla-gen PRIVATE res)

# Generate Headers
add_custom_command(OUTPUT generated/op.h generated/opcode.h
  COMMAND rm -f generated/op.h
  COMMAND mkdir -p generated
  COMMAND $<TARGET_FILE:dla-gen> --gen-include-all-header > generated/op.h
  COMMAND $<TARGET_FILE:dla-gen> --gen-opcode-header > generated/opcode.h
  COMMENT "Generate op headers"
  DEPENDS dla-gen
)

add_executable(dla-dbg dbg.cpp generated/op.h generated/opcode.h src/op/RELU.cpp)
target_include_directories(dla-dbg PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)
target_include_directories(dla-dbg PRIVATE res)
target_include_directories(dla-dbg PRIVATE src)
set_target_properties(dla-dbg PROPERTIES
  CXX_STANDARD 14
)
