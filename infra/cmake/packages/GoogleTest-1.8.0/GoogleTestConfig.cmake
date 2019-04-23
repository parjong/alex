# TODO Make this code resuable
function(_GoogleTest_Build)
  set(VERSION "1.8.0")
  set(PREFIX "GOOGLETEST-${VERSION}")

  alex_find_package(GoogleTestSource EXACT ${VERSION} QUIET)

  if(NOT GoogleTestSource_FOUND)
    return()
  endif(NOT GoogleTestSource_FOUND)

  set(STAMP_PATH "${ALEX_OVERLAY_DIR}/${PREFIX}.stamp")

  if(EXISTS "${STAMP_PATH}")
    return()
  endif(EXISTS "${STAMP_PATH}")

  set(CONFIGURE_LOG "${ALEX_PROJECT_BINARY_DIR}/overlay-build/${PREFIX}.configure.log")
  set(BUILD_LOG "${ALEX_PROJECT_BINARY_DIR}/overlay-build/${PREFIX}.build.log")

  set(BUILD_DIR "${ALEX_PROJECT_BINARY_DIR}/overlay-build/${PREFIX}")
  set(INSTALL_DIR "${ALEX_OVERLAY_DIR}")

  file(MAKE_DIRECTORY "${ALEX_OVERLAY_DIR}")
  file(MAKE_DIRECTORY "${BUILD_DIR}")

  file(WRITE "${STAMP_PATH}")

  message(STATUS "Configure Google Test ${VERSION} (source: ${GoogleTestSource_DIR})'")

  execute_process(COMMAND ${CMAKE_COMMAND} "${GoogleTestSource_DIR}"
                          -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
                  OUTPUT_FILE "${CONFIGURE_LOG}"
                  ERROR_FILE "${CONFIGURE_LOG}"
                  RESULT_VARIABLE RESULT
                  WORKING_DIRECTORY "${BUILD_DIR}")

  if(NOT RESULT EQUAL 0)
    return()
  endif(NOT RESULT EQUAL 0)

  message(STATUS "Configure Google Test ${VERSION}  - done")

  message(STATUS "Build and Install Google Test ${VERSION}")

  execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install
                  OUTPUT_FILE "${BUILD_LOG}"
                  ERROR_FILE "${BUILD_LOG}"
                  RESULT_VARIABLE RESULT
                  WORKING_DIRECTORY "${BUILD_DIR}")

  if(NOT RESULT EQUAL 0)
    return()
  endif(NOT RESULT EQUAL 0)

  message(STATUS "Build and Install Google Test ${VERSION} - done")
endfunction(_GoogleTest_Build)

macro(_GoogleTest_Import)
  find_package(GTest QUIET)
endmacro(_GoogleTest_Import)

_GoogleTest_Build()
_GoogleTest_Import()
