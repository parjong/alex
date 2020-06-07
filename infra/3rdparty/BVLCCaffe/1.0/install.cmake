message(STATUS "PKG_SOURCE_DIR: ${PKG_SOURCE_DIR}")
message(STATUS "PKG_BUILD_DIR: ${PKG_BUILD_DIR}")
message(STATUS "PKG_INSTALL_DIR: ${PKG_INSTALL_DIR}")

execute_process(
  # TODO Move this code to "3rdparty-install.cmake"
  COMMAND ${CMAKE_COMMAND} -E make_directory ${PKG_BUILD_DIR}
  # TODO Move this code to "3rdparty-install.cmake"
  COMMAND ${CMAKE_COMMAND} -E make_directory ${PKG_INSTALL_DIR}
)

execute_process(
  COMMAND ${CMAKE_COMMAND}
    "${PKG_SOURCE_DIR}"
    -DCPU_ONLY=TRUE
    -DBUILD_SHARED_LIBS=FALSE
    -DBUILD_python=FALSE
    -DUSE_OPENCV=FALSE
    -DCMAKE_INSTALL_PREFIX=${PKG_INSTALL_DIR}
  COMMAND make all install
  WORKING_DIRECTORY "${PKG_BUILD_DIR}"
)
