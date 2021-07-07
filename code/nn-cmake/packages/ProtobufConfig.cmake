function(_Protobuf_Import)
  find_package(Protobuf)

  if(NOT Protobuf_FOUND)
    set(Protobuf_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT Protobuf_FOUND)

  if(TARGET libprotobuf OR TARGET protoc)
    set(Protobuf_FOUND TRUE PARENT_SCOPE)
    return()
  endif(TARGET libprotobuf OR TARGET protoc)

  add_library(libprotobuf INTERFACE)
  target_include_directories(libprotobuf INTERFACE ${PROTOBUF_INCLUDE_DIRS})
  target_link_libraries(libprotobuf INTERFACE ${PROTOBUF_LIBRARIES})

  add_executable(protoc IMPORTED GLOBAL)
  set_target_properties(protoc PROPERTIES IMPORTED_LOCATION ${PROTOBUF_PROTOC_EXECUTABLE})

  set(Protobuf_FOUND TRUE PARENT_SCOPE)
endfunction(_Protobuf_Import)

_Protobuf_Import()

if(Protobuf_FOUND)
  function(Protobuf_Generate PREFIX OUTPUT_DIR PROTO_DIR)
    get_filename_component(abs_output_dir ${OUTPUT_DIR} ABSOLUTE)
    get_filename_component(abs_proto_dir ${PROTO_DIR} ABSOLUTE)

    foreach(proto ${ARGN})
      get_filename_component(fil "${proto}" NAME)
      get_filename_component(dir "${proto}" DIRECTORY)

      get_filename_component(fil_we "${fil}" NAME_WE)

      get_filename_component(abs_fil "${abs_proto_base}/${proto}" ABSOLUTE)
      get_filename_component(abs_dir "${abs_fil}" DIRECTORY)

      list(APPEND PROTO_FILES "${abs_proto_dir}/${proto}")
      list(APPEND OUTPUT_FILES "${abs_output_dir}/${dir}/${fil_we}.pb.h")
      list(APPEND OUTPUT_FILES "${abs_output_dir}/${dir}/${fil_we}.pb.cc")
    endforeach()

    add_custom_command(OUTPUT ${OUTPUT_FILES}
      COMMAND ${CMAKE_COMMAND} -E make_directory "${abs_output_dir}"
      COMMAND "$<TARGET_FILE:protoc>" --cpp_out "${abs_output_dir}" -I "${abs_proto_dir}" ${PROTO_FILES})

    set(${PREFIX}_SOURCES ${OUTPUT_FILES} PARENT_SCOPE)
    set(${PREFIX}_INCLUDE_DIRS ${abs_output_dir} PARENT_SCOPE)
  endfunction()
endif(Protobuf_FOUND)
