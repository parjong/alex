###
### Alex Extended Infrastructure
###
if(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)
  message(FATAL_ERROR "ALEX_PROJECT_SOURCE_DIR is not defined")
endif(NOT DEFINED ALEX_PROJECT_SOURCE_DIR)

# alex_3rdparty_property(VAR PACKAGE <NAME> VERSION <VERSION> PROPERTY [URL|SOURCE_DIR|BUILD_DIR|INSTALL_DIR])
# alex_3rdparty_download(PACKAGE <NAME> VERSION <VERSION>)
# 3rdparty_install(PACKAGE ... VERSION ...)
# 3rdparty_uninstall(PACKAGE ... VERSION ...)

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

  alex_include(StampTools)
  alex_include(ExternalSource)

  set(_INFO_DIR "${ALEX_PROJECT_SOURCE_DIR}/infra/3rdparty/${_NAME}/${_VERSION}")
  # TODO Read URL.user if exists
  file(STRINGS "${_INFO_DIR}/URL" _URL)

  set(SRC_DIR "${ALEX_PROJECT_SOURCE_DIR}/externals/src")

  set(STAMP_FILE "${SRC_DIR}/${_NAME}-${_VERSION}.stamp")

  Stamp_Check(STAMP_VALID "${STAMP_FILE}" "${_URL}")
  Stamp_Remove_Unless("${STAMP_FILE}" "${STAMP_VALID}")

  if(NOT STAMP_VALID)
    ExternalSource_Download(${_NAME}
      DOWNLOAD_ONLY
      URL "${_URL}"
      OUTPUT_DIRECTORY "${SRC_DIR}/${_NAME}-${_VERSION}"
      WORKING_DIRECTORY "${SRC_DIR}/${_NAME}-${_VERSION}-tmp"
    )

    Stamp_Create("${STAMP_FILE}" "${_URL}")
  endif()

  set(${_NAME}_DIR "${SRC_DIR}/${_NAME}-${_VERSION}" PARENT_SCOPE)
endfunction(alex_3rdparty_download)

function(alex_3rdparty_install PKG_PACKAGE PKG_VERSION)
  alex_include(ExternalSource)

  set(PKG_INFO_DIR "${ALEX_PROJECT_SOURCE_DIR}/infra/3rdparty/${PKG_PACKAGE}/${PKG_VERSION}")
  set(PKG_SOURCE_DIR "${ALEX_PROJECT_SOURCE_DIR}/externals/${PKG_PACKAGE}-${PKG_VERSION}")
  set(PKG_BUILD_DIR "${ALEX_PROJECT_SOURCE_DIR}/overlay/${PKG_PACKAGE}-${PKG_VERSION}-build")
  set(PKG_INSTALL_DIR "${ALEX_PROJECT_SOURCE_DIR}/overlay/${PKG_PACKAGE}-${PKG_VERSION}")

  include("${PKG_INFO_DIR}/install.cmake")
endfunction(alex_3rdparty_install)

# TODO Rewrite ExternalSource_Download as a PURE helper
#
# DO NOT CHECK STAMP
# DO NOT MANAGE EXTERNAL DIRECTORIES
#
# AlexTools SHOULD BE responsible for these tasks!
