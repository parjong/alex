# TODO Validate the argument of "requires"
function(Alex_GetModuleOrder VAR)
  # This file will describe the dependencies among projects
  set(DEPS_FILE "${CMAKE_CURRENT_BINARY_DIR}/contrib.deps")

  # Remove .deps file
  file(REMOVE "${DEPS_FILE}")

  # Let's create .deps file
  file(GLOB CHILD_PROJECTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/CMakeLists.txt")

  unset(PROJECT_DIRS)
  foreach(CHILD_PROJECT IN ITEMS ${CHILD_PROJECTS})
    get_filename_component(PROJECT_DIR ${CHILD_PROJECT} DIRECTORY)
    list(APPEND PROJECT_DIRS ${PROJECT_DIR})
  endforeach(CHILD_PROJECT)

  foreach(PROJECT_DIR IN ITEMS ${PROJECT_DIRS})
    set(SUCC "${PROJECT_DIR}")
    set(REQUIRES_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_DIR}/requires.cmake")

    macro(require PRED)
      file(APPEND "${DEPS_FILE}" "${PRED} ${SUCC}\n")
    endmacro(require)

    file(APPEND "${DEPS_FILE}" "${SUCC} ${SUCC}\n")
    if(EXISTS "${REQUIRES_FILE}")
      include(${REQUIRES_FILE})
    endif(EXISTS "${REQUIRES_FILE}")
  endforeach(PROJECT_DIR)

  # NOTE "tsort" is a part of the POSIX.1 standard.
  #
  # Reference: http://pubs.opengroup.org/onlinepubs/9699919799/utilities/tsort.html
  execute_process(COMMAND tsort "${DEPS_FILE}"
                  OUTPUT_VARIABLE ORDER
                  OUTPUT_STRIP_TRAILING_WHITESPACE)

  # Remove newline characters
  # TODO Check which one (UNIX_COMMAND or WINDOWS_COMMAND) is correct
  separate_arguments(ORDER UNIX_COMMAND ${ORDER})

  set(${VAR} "${ORDER}" PARENT_SCOPE)
endfunction(Alex_GetModuleOrder)

function(Alex_AddModule DIR)
  # TODO Support Automatic Configuration
  # TODO Support Per-module On/Off Configuration
  message(STATUS "Adding '${DIR}' module")
  add_subdirectory(${DIR})
endfunction(Alex_AddModule)

function(Alex_AddModules)
  Alex_GetModuleOrder(PROJECT_DIRS)

  foreach(PROJECT_DIR IN ITEMS ${PROJECT_DIRS})
    Alex_AddModule(${PROJECT_DIR})
  endforeach(PROJECT_DIR)
endfunction(Alex_AddModules)

Alex_AddModules()
