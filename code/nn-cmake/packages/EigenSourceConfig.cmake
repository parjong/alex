function(_EigenSource_Import)
  nn_include(ExternalSource)

  if(NOT DEFINED EIGEN_URL)
    set(EIGEN_URL https://bitbucket.org/eigen/eigen/get/6913f0cf7d06.tar.gz)
  endif(NOT DEFINED EIGEN_URL)

  ExternalSource_Download(EIGEN "${EIGEN_URL}")

  set(EigenSource_DIR "${EIGEN_SOURCE_DIR}" PARENT_SCOPE)
  set(EigenSource_FOUND TRUE PARENT_SCOPE)
endfunction(_EigenSource_Import)

_EigenSource_Import()
