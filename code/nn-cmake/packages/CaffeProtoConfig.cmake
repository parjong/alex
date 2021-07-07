function(_CaffeProto_Import)
  nn_find_package(CaffeSource)

  if(NOT CaffeSource_FOUND)
    set(CaffeProto_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT CaffeSource_FOUND)

  nn_find_package(Protobuf)

  if(NOT Protobuf_FOUND)
    set(CaffeProto_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT Protobuf_FOUND)

  if(NOT TARGET caffeproto)
    nn_include(ExternalProject)
    add_extdirectory("${CMAKE_CURRENT_LIST_DIR}/CaffeProto" caffeproto)
  endif(NOT TARGET caffeproto)

  set(CaffeProto_FOUND TRUE PARENT_SCOPE)
endfunction(_CaffeProto_Import)

_CaffeProto_Import()
