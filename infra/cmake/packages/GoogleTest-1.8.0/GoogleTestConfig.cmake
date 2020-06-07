# TODO Make this code resuable
function(_GoogleTest_Build)
  set(VERSION "1.8.0")
  set(PREFIX "GOOGLETEST-${VERSION}")

  # Q. Who is responsible for this?
  alex_find_package(GoogleTestSource EXACT ${VERSION} QUIET)

  if(NOT GoogleTestSource_FOUND)
    return()
  endif(NOT GoogleTestSource_FOUND)

  # TODO Let 3rparty installer be responsible for STAMP management
  set(STAMP_PATH "${ALEX_OVERLAY_DIR}/${PREFIX}.stamp")

  if(EXISTS "${STAMP_PATH}")
    return()
  endif(EXISTS "${STAMP_PATH}")

  # TODO Let 3rparty installer manage BUILD_DIR and INSTALL_DIR
  set(SOURCE_DIR "${GoogleTestSource_DIR}")
  set(BUILD_DIR "${ALEX_PROJECT_BINARY_DIR}/overlay-build/${PREFIX}")
  set(INSTALL_DIR "${ALEX_OVERLAY_DIR}/${PREFIX}")

  file(MAKE_DIRECTORY "${ALEX_OVERLAY_DIR}")
  file(MAKE_DIRECTORY "${BUILD_DIR}")

  message(STATUS "Configure Google Test ${VERSION} (source: ${SOURCE_DIR})'")

  execute_process(COMMAND ${CMAKE_COMMAND} "${SOURCE_DIR}" -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
                  RESULT_VARIABLE RESULT
                  WORKING_DIRECTORY "${BUILD_DIR}")

  if(NOT RESULT EQUAL 0)
    return()
  endif(NOT RESULT EQUAL 0)

  message(STATUS "Configure Google Test ${VERSION}  - done")

  message(STATUS "Build and Install Google Test ${VERSION}")

  execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install
                  RESULT_VARIABLE RESULT
                  WORKING_DIRECTORY "${BUILD_DIR}")

  if(NOT RESULT EQUAL 0)
    return()
  endif(NOT RESULT EQUAL 0)

  message(STATUS "Build and Install Google Test ${VERSION} - done")

  list(APPEND CMAKE_PREFIX_PATH "${INSTALL_DIR}")
  set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" PARENT_SCOPE)

  # TODO Clean up before install
  file(WRITE "${STAMP_PATH}")
endfunction(_GoogleTest_Build)

macro(_GoogleTest_Import)
  find_package(GTest QUIET)
endmacro(_GoogleTest_Import)

_GoogleTest_Build()
_GoogleTest_Import()
