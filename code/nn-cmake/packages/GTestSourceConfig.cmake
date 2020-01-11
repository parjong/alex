function(_GTestSource_Import)
  nn_include(ExternalSource)

  if(NOT DEFINED GTEST_URL)
    set(GTEST_URL https://github.com/google/googletest/archive/release-1.8.0.tar.gz)
  endif(NOT DEFINED GTEST_URL)

  ExternalSource_Download(GTEST "${GTEST_URL}")

  set(GTestSource_DIR "${GTEST_SOURCE_DIR}" PARENT_SCOPE)
  set(GTestSource_FOUND TRUE PARENT_SCOPE)
endfunction(_GTestSource_Import)

_GTestSource_Import()
