find_package(Protobuf MODULE QUIET)

message(STATUS "Found Protobuf: ${PROTOBUF_FOUND}")

if(NOT PROTOBUF_FOUND)
  return()
endif(NOT PROTOBUF_FOUND)

# Protobuf_Generate(PREFIX SOURCE_DIR ... OUTPUT_DIR ... FILES <relative .proto paths>)
#
# Protobuf_Generate will update the following variables:
# - <PREFIX>_SOURCES
# - <PREFIX>_INCLUDE_DIRS
# - <PREFIX>_LIBRARIES
function(Protobuf_Generate PREFIX)
  set(ONE_VALUE_KEYWORDS SOURCE_DIR OUTPUT_DIR)
  set(MULTI_VALUE_KEYWORDS FILES)
  cmake_parse_arguments(ARG "" "${ONE_VALUE_KEYWORDS}" "${MULTI_VALUE_KEYWORDS}" ${ARGN})

  set(OUTPUT_DIR ${ARG_OUTPUT_DIR})
  set(SOURCE_DIR ${ARG_SOURCE_DIR})

  get_filename_component(abs_output_dir ${OUTPUT_DIR} ABSOLUTE)
  get_filename_component(abs_source_dir ${SOURCE_DIR} ABSOLUTE)

  # Reset list variables before their first use
  # NOTE THIS DOES NOT AFFECT variables in the parent scope
  unset(PROTO_FILES)
  unset(GENERATED_FILES)

  foreach(proto ${ARG_FILES})
    get_filename_component(fil "${proto}" NAME)
    get_filename_component(dir "${proto}" DIRECTORY)

    get_filename_component(fil_we "${fil}" NAME_WE)
    get_filename_component(abs_fil "${abs_proto_base}/${proto}" ABSOLUTE)
    get_filename_component(abs_dir "${abs_fil}" DIRECTORY)

    list(APPEND PROTO_FILES "${abs_source_dir}/${proto}")
    list(APPEND GENERATED_FILES "${abs_output_dir}/${dir}/${fil_we}.pb.h")
    list(APPEND GENERATED_FILES "${abs_output_dir}/${dir}/${fil_we}.pb.cc")
  endforeach()

  add_custom_command(
    OUTPUT ${GENERATED_FILES}
    # Create output directory
    COMMAND ${CMAKE_COMMAND} -E make_directory "${abs_output_dir}"
    # Generate files
    COMMAND "${PROTOBUF_PROTOC_EXECUTABLE}" --cpp_out "${abs_output_dir}" -I "${abs_source_dir}" ${PROTO_FILES}
    DEPENDS ${PROTO_FILES}
  )

  set(${PREFIX}_SOURCES ${GENERATED_FILES} PARENT_SCOPE)
  set(${PREFIX}_INCLUDE_DIRS ${abs_output_dir} PARENT_SCOPE)
  set(${PREFIX}_LIBRARIES ${PROTOBUF_LIBRARY} PARENT_SCOPE)
endfunction(Protobuf_Generate)

# TODO Implement Protobuf_Target(TGT SOURCE_DIR ... OUTPUT_DIR ... FILES ...)
