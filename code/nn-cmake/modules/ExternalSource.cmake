function(ExternalSource_Download PREFIX URL)
  set(EXTERNAL_DIR "${NN_SOURCE_DIR}/externals")

  set(SOURCE_DIR "${EXTERNAL_DIR}/${PREFIX}")
  set(STAMP_FILE "${EXTERNAL_DIR}/${PREFIX}.stamp")

  if(EXISTS "${STAMP_FILE}")
    file(READ "${STAMP_FILE}" STAMP_URL)

    if(NOT STAMP_URL STREQUAL URL)
      file(REMOVE "${STAMP_FILE}")
    endif()
  endif()

  if(NOT EXISTS "${STAMP_FILE}")
    set(WORKING_DIR "${EXTERNAL_DIR}/${PREFIX}-tmp")

    get_filename_component(DOWNLOAD_FILENAME ${URL} NAME)

    set(DOWNLOAD_DIR "${WORKING_DIR}/download")
    set(DOWNLOAD_FILE "${DOWNLOAD_DIR}/${DOWNLOAD_FILENAME}")

    set(UNZIP_DIR "${WORKING_DIR}/unzip")

    file(REMOVE_RECURSE "${SOURCE_DIR}" "${WORKING_DIR}")

    file(MAKE_DIRECTORY "${DOWNLOAD_DIR}")
    file(MAKE_DIRECTORY "${UNZIP_DIR}")

    message("-- Download ${PREFIX} from ${URL}")
    file(DOWNLOAD ${URL} "${DOWNLOAD_FILE}")
    message("-- Download ${PREFIX} from ${URL} - done")

    message("-- Extract ${PREFIX}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xfz "${DOWNLOAD_FILE}"
      WORKING_DIRECTORY "${UNZIP_DIR}")
    message("-- Extract ${PREFIX} - done")

    message("-- Analyze and prepare ${PREFIX}")
    file(GLOB contents "${UNZIP_DIR}/*")
    list(LENGTH contents n)
    if(NOT n EQUAL 1 OR NOT IS_DIRECTORY "${contents}")
      set(contents "${UNZIP_DIR}")
    endif()

    get_filename_component(contents ${contents} ABSOLUTE)

    file(RENAME ${contents} "${SOURCE_DIR}")
    message("-- Analyze and prepare ${PREFIX} - done")

    file(REMOVE_RECURSE "${WORKING_DIR}")
    file(WRITE "${STAMP_FILE}" "${URL}")
  endif()

  set(${PREFIX}_SOURCE_DIR "${SOURCE_DIR}" PARENT_SCOPE)
endfunction()
