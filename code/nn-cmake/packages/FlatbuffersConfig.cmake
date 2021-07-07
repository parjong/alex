function(_Flatbuffers_Import)
  nn_find_package(FlatbuffersSource)

  if(NOT FlatbuffersSource_FOUND)
    set(Flatbuffers_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT FlatbuffersSource_FOUND)

  if(NOT TARGET flatbuffers)
    nn_include(ExternalProject)
    add_extdirectory("${CMAKE_CURRENT_LIST_DIR}/Flatbuffers" flatbuffer)
  endif(NOT TARGET flatbuffers)

  set(Flatbuffers_FOUND TRUE PARENT_SCOPE)
endfunction(_Flatbuffers_Import)

_Flatbuffers_Import()
