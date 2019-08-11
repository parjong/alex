# TODO Support (GLOBAL) verbose level control
# TODO Support MD5 HASH check
function(ExternalSource_Download PREFIX)
  include(CMakeParseArguments)
  alex_include(StampTools)

  set(SingleValueArgs URL DIRNAME)

  cmake_parse_arguments(ARG "" "${SingleValueArgs}" "" ${ARGN})

  if(NOT ARG_URL)
    message(FATAL_ERROR "URL is missing")
  endif(NOT ARG_URL)

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

    get_filename_component(DOWNLOAD_FILENAME ${URL} NAME)

    set(DOWNLOAD_DIR "${WORKING_DIR}/download")
    set(DOWNLOAD_FILE "${DOWNLOAD_DIR}/${DOWNLOAD_FILENAME}")

    set(UNZIP_DIR "${WORKING_DIR}/unzip")

    file(REMOVE_RECURSE "${SOURCE_DIR}" "${WORKING_DIR}")

    file(MAKE_DIRECTORY "${DOWNLOAD_DIR}")
    file(MAKE_DIRECTORY "${UNZIP_DIR}")

    message(STATUS "Download ${PREFIX} from ${URL}")
    file(DOWNLOAD ${URL} "${DOWNLOAD_FILE}")
    message(STATUS "Download ${PREFIX} from ${URL} - done")

    message(STATUS "Extract ${PREFIX}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xfz "${DOWNLOAD_FILE}"
                    WORKING_DIRECTORY "${UNZIP_DIR}")
    # TODO Check exitcode
    message(STATUS "Extract ${PREFIX} - done")

    message(STATUS "Analyze and prepare ${PREFIX}")
    file(GLOB contents "${UNZIP_DIR}/*")
    list(LENGTH contents n)
    if(NOT n EQUAL 1 OR NOT IS_DIRECTORY "${contents}")
      set(contents "${UNZIP_DIR}")
    endif()

    get_filename_component(contents ${contents} ABSOLUTE)

    file(RENAME ${contents} "${SOURCE_DIR}")
    message(STATUS "Analyze and prepare ${PREFIX} - done")

    file(REMOVE_RECURSE "${WORKING_DIR}")
    file(WRITE "${STAMP_FILE}" "${URL}")
  endif()

  set(${PREFIX}_SOURCE_DIR "${SOURCE_DIR}" PARENT_SCOPE)
endfunction(ExternalSource_Download)
