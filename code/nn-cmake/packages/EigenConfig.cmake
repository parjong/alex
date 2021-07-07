function(_Eigen_Import)
  nn_include(ExternalSource)

  nn_find_package(EigenSource QUIET)

  if(NOT EigenSource_FOUND)
    set(Eigen_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT EigenSource_FOUND)

  if(NOT TARGET eigen)
    add_library(eigen INTERFACE)
    target_include_directories(eigen INTERFACE ${EigenSource_DIR})

    message(STATUS "Found Eigen (include: ${EigenSource_DIR})")
  endif(NOT TARGET eigen)

  set(Eigen_FOUND TRUE PARENT_SCOPE)
endfunction(_Eigen_Import)

_Eigen_Import()
