function(_Farmhash_Import)
  nn_find_package(FarmhashSource QUIET)

  if(NOT FarmhashSource_FOUND)
    set(Farmhash_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT FarmhashSource_FOUND)

  if(NOT TARGET farmhash)
    nn_include(ExternalProject)
    add_extdirectory("${CMAKE_CURRENT_LIST_DIR}/Farmhash" farmhash)
  endif(NOT TARGET farmhash)

  set(Farmhash_FOUND TRUE PARENT_SCOPE)
endfunction(_Farmhash_Import)

_Farmhash_Import()
