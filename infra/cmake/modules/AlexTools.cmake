###
### Alex Extended Infrastructure
###
if(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)
  message(FATAL_ERROR "ALEX_PROJECT_SOURCE_DIR is not defined")
endif(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)

function(alex_3rdparty_download)
  cmake_parse_arguments(ARG "" "PACKAGE;VERSION" "" ${ARGN})

  if(NOT ARG_PACKAGE)
    message(FATAL_ERROR "PACKAGE is missing")
  endif(NOT ARG_PACKAGE)

  if(NOT ARG_VERSION)
    message(FATAL_ERROR "VERSION is missing")
  endif(NOT ARG_VERSION)

  set(_NAME ${ARG_PACKAGE})
  set(_VERSION ${ARG_VERSION})

  alex_include(ExternalSource)

  set(_INFO_DIR "${ALEX_PROJECT_SOURCE_DIR}/infra/3rdparty/${_NAME}/${_VERSION}")
  # TODO Read URL.user if exists
  file(STRINGS "${_INFO_DIR}/URL" _URL)

  ExternalSource_Download(${_NAME} DIRNAME "${_NAME}-${_VERSION}" URL "${_URL}")

  set(${_NAME}_DIR "${${_NAME}_SOURCE_DIR}" PARENT_SCOPE)
endfunction(alex_3rdparty_download)
