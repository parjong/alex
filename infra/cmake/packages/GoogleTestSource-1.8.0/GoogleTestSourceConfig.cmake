function(_GoogleTestSource_Download)
  alex_include(ExternalSource)

  # TODO Allow users to control whether to download source code or not
  # TODO Allow users to specify URL for specific version with the same CMake configuration
  set(GOOGLETEST_URL "https://github.com/google/googletest/archive/release-1.8.0.tar.gz" CACHE STRING "Google Test 1.8.0 source URL")

  ExternalSource_Download(GOOGLETEST DIRNAME GOOGLETEST-1.8.0 URL "${GOOGLETEST_URL}")

  # Set FALSE on download failure
  set(GoogleTestSource_DIR "${GOOGLETEST_SOURCE_DIR}" PARENT_SCOPE)
  set(GoogleTestSource_FOUND TRUE PARENT_SCOPE)
endfunction(_GoogleTestSource_Download)

_GoogleTestSource_Download()
