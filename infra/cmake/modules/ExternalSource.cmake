# _Download(NAME ... URL ... OUTPUT_DIRECTORY ... WORKING_DIRECTORY ...)
function(_Download)
  include(CMakeParseArguments)
  cmake_parse_arguments(ARG "" "NAME;URL;OUTPUT_DIRECTORY;WORKING_DIRECTORY" "" ${ARGN})

  if(NOT ARG_NAME)
    message(FATAL_ERROR "NAME is missing")
  endif(NOT ARG_NAME)

  if(NOT ARG_URL)
    message(FATAL_ERROR "URL is missing")
  endif(NOT ARG_URL)

  if(NOT ARG_OUTPUT_DIRECTORY)
    message(FATAL_ERROR "OUTPUT_DIRECTORY is missing")
  endif(NOT ARG_OUTPUT_DIRECTORY)

  if(NOT ARG_WORKING_DIRECTORY)
    message(FATAL_ERROR "WORKING_DIRECTORY is missing")
  endif(NOT ARG_WORKING_DIRECTORY)

  set(NAME "${ARG_NAME}")
  set(URL "${ARG_URL}")
  set(OUT_DIR "${ARG_OUTPUT_DIRECTORY}")
  set(TMP_DIR "${ARG_WORKING_DIRECTORY}")

  get_filename_component(_EXT ${URL} EXT)

  set(DOWNLOADED_FILE "${TMP_DIR}/download.${_EXT}")
  set(UNZIPPED_DIR "${TMP_DIR}/unzipped")

  file(REMOVE_RECURSE "${OUT_DIR}" "${TMP_DIR}")

  file(MAKE_DIRECTORY "${TMP_DIR}")
  file(MAKE_DIRECTORY "${UNZIPPED_DIR}")

  message(STATUS "Download ${NAME} from ${URL}")
  file(DOWNLOAD ${URL} "${DOWNLOADED_FILE}")
  message(STATUS "Download ${NAME} from ${URL} - done")

  message(STATUS "Extract ${NAME}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xfz "${DOWNLOADED_FILE}"
                  WORKING_DIRECTORY "${UNZIPPED_DIR}")
  # TODO Check exitcode
  message(STATUS "Extract ${NAME} - done")

  message(STATUS "Analyze and prepare ${NAME}")
  file(GLOB contents "${UNZIPPED_DIR}/*")
  list(LENGTH contents n)
  if(NOT n EQUAL 1 OR NOT IS_DIRECTORY "${contents}")
    set(contents "${UNZIPPED_DIR}")
  endif()

  get_filename_component(contents ${contents} ABSOLUTE)

  file(RENAME ${contents} "${OUT_DIR}")
  message(STATUS "Analyze and prepare ${NAME} - done")

  # WARNING! file(REMOVE_RECURE) removes the current source directory!
  # TODO Implement "Guard"
  file(REMOVE_RECURSE "${TMP_DIR}")
endfunction(_Download)

# TODO Support (GLOBAL) verbose level control
# TODO Support MD5 HASH check
function(ExternalSource_Download PREFIX)
  include(CMakeParseArguments)
  alex_include(StampTools)

  set(SingleValueArgs URL DIRNAME OUTPUT_DIRECTORY WORKING_DIRECTORY)

  cmake_parse_arguments(ARG "DOWNLOAD_ONLY" "${SingleValueArgs}" "" ${ARGN})

  if(NOT ARG_URL)
    message(FATAL_ERROR "URL is missing")
  endif(NOT ARG_URL)

  if(ARG_DOWNLOAD_ONLY)
    if(NOT ARG_OUTPUT_DIRECTORY)
      message(FATAL_ERROR)
    endif(NOT ARG_OUTPUT_DIRECTORY)

    if(NOT ARG_WORKING_DIRECTORY)
      message(FATAL_ERROR)
    endif(NOT ARG_WORKING_DIRECTORY)

    _Download(
      NAME "${PREFIX}"
      URL "${ARG_URL}"
      OUTPUT_DIRECTORY "${ARG_OUTPUT_DIRECTORY}"
      WORKING_DIRECTORY "${ARG_WORKING_DIRECTORY}"
    )

    set(${PREFIX}_SOURCE_DIR "${SOURCE_DIR}" PARENT_SCOPE)
    return()
  endif(ARG_DOWNLOAD_ONLY)

  if(ARG_DIRNAME)
    set(DIRNAME "${ARG_DIRNAME}")
  else(ARG_DIRNAME)
    set(DIRNAME "${PREFIX}")
  endif(ARG_DIRNAME)

  set(URL "${ARG_URL}")
  set(EXTERNAL_DIR "${ALEX_PROJECT_SOURCE_DIR}/externals")

  set(SOURCE_DIR "${EXTERNAL_DIR}/${DIRNAME}")
  set(STAMP_FILE "${EXTERNAL_DIR}/${DIRNAME}.stamp")

  Stamp_Check(STAMP_VALID "${STAMP_FILE}" "${URL}")

  if(NOT STAMP_VALID)
    # Remove invalid STAMP
    if(EXISTS "${STAMP_FILE}")
      file(REMOVE "${STAMP_FILE}")
    endif(EXISTS "${STAMP_FILE}")
  endif(NOT STAMP_VALID)

  if(NOT STAMP_VALID)
    set(WORKING_DIR "${EXTERNAL_DIR}/${DIRNAME}-tmp")

    _Download(
      NAME "${PREFIX}"
      URL "${URL}"
      OUTPUT_DIRECTORY "${SOURCE_DIR}"
      WORKING_DIRECTORY "${WORKING_DIR}"
    )

    file(WRITE "${STAMP_FILE}" "${URL}")
  endif()

  set(${PREFIX}_SOURCE_DIR "${SOURCE_DIR}" PARENT_SCOPE)
endfunction(ExternalSource_Download)
