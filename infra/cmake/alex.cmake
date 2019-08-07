###
### Alex Core Infrastructure
###
if(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)
  message(FATAL_ERROR "ALEX_PROJECT_SOURCE_DIR is not defined")
endif(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)

macro(alex_include PREFIX)
  include("${ALEX_PROJECT_SOURCE_DIR}/infra/cmake/modules/${PREFIX}.cmake")
endmacro(alex_include)

macro(alex_find_package PREFIX)
  find_package(${PREFIX} CONFIG NO_DEFAULT_PATH PATHS "${ALEX_PROJECT_SOURCE_DIR}/infra/cmake/packages" ${ARGN})
endmacro(alex_find_package)
