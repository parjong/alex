function(_GFlags_Import)
  include(FindPackageHandleStandardArgs)

  set(GFLAGS_ROOT_DIR "" CACHE PATH "Folder contains Gflags")

  find_path(GFLAGS_INCLUDE_DIR gflags/gflags.h PATHS ${GFLAGS_ROOT_DIR})
  find_library(GFLAGS_LIBRARY gflags)

  find_package_handle_standard_args(GFlags DEFAULT_MSG GFLAGS_INCLUDE_DIR GFLAGS_LIBRARY)

  if(NOT GFLAGS_FOUND)
    set(GFlags_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT GFLAGS_FOUND)

  set(GFLAGS_INCLUDE_DIRS ${GFLAGS_INCLUDE_DIR})
  set(GFLAGS_LIBRARIES ${GFLAGS_LIBRARY})
  message(STATUS "Found gflags  (include: ${GFLAGS_INCLUDE_DIR}, library: ${GFLAGS_LIBRARY})")
  mark_as_advanced(GFLAGS_LIBRARY_DEBUG GFLAGS_LIBRARY_RELEASE
                   GFLAGS_LIBRARY GFLAGS_INCLUDE_DIR GFLAGS_ROOT_DIR)

  if(NOT TARGET gflags)
    add_library(gflags INTERFACE)
    target_include_directories(gflags INTERFACE ${GFLAGS_INCLUDE_DIR})
    target_link_libraries(gflags INTERFACE ${GFLAGS_LIBRARY})
  endif(NOT TARGET gflags)

  set(GFlags_FOUND TRUE PARENT_SCOPE)
  return()
endfunction(_GFlags_Import)

_GFlags_Import()
