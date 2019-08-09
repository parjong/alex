#
# "alex 3rdparty download" command bridge (BASH -> CMake)
#
if(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)
  message(FATAL_ERROR "ALEX_PROJECT_SOURCE_DIR is missing")
endif(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)

if(NOT DEFINED PKG_NAME)
  message(FATAL_ERROR "PKG_NAME is missing")
endif(NOT DEFINED PKG_NAME)

if(NOT DEFINED PKG_VERSION)
  message(FATAL_ERROR "PKG_VERSION is missing")
endif(NOT DEFINED PKG_VERSION)

include("${ALEX_PROJECT_SOURCE_DIR}/infra/cmake/alex.cmake")

alex_include(AlexTools)
alex_3rdparty_download(PACKAGE ${PKG_NAME} VERSION ${PKG_VERSION})
