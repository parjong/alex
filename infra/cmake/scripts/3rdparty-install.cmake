#
# "alex 3rdparty install" command bridge (BASH -> CMake)
#

if(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)
  message(FATAL_ERROR)
endif(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)

# TODO Check PKG_NAME
# TODO Check PKG_VERSION

include("${ALEX_PROJECT_SOURCE_DIR}/infra/cmake/alex.cmake")

alex_include(AlexTools)
alex_3rdparty_install(${PKG_NAME} ${PKG_VERSION})
