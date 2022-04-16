function(_GTest_Build)
  nn_find_package(GTestSource QUIET)

  if(NOT GTestSource_FOUND)
    set(GTest_FOUND FALSE PARENT_SCOPE)
    return()
  endif()

  if(NOT TARGET gtest)
    nn_include(ExternalProject)
    add_extdirectory("${GTestSource_DIR}" gtest)
  endif(NOT TARGET gtest)

  set(GTest_FOUND TRUE PARENT_SCOPE)
endfunction(_GTest_Build)

_GTest_Build()
