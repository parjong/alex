function(_GLog_Import)
  include(FindPackageHandleStandardArgs)

  set(GLOG_ROOT_DIR "" CACHE PATH "Folder contains Google glog")

  find_path(GLOG_INCLUDE_DIR glog/logging.h PATHS ${GLOG_ROOT_DIR})

  find_library(GLOG_LIBRARY glog PATHS ${GLOG_ROOT_DIR}
                                 PATH_SUFFIXES lib lib64)

  find_package_handle_standard_args(Glog DEFAULT_MSG GLOG_INCLUDE_DIR GLOG_LIBRARY)

  if(NOT GLOG_FOUND)
    set(GLog_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT GLOG_FOUND)

  set(GLOG_INCLUDE_DIRS ${GLOG_INCLUDE_DIR})
  set(GLOG_LIBRARIES ${GLOG_LIBRARY})

  mark_as_advanced(GLOG_ROOT_DIR)
  mark_as_advanced(GLOG_LIBRARY_RELEASE GLOG_LIBRARY_DEBUG GLOG_LIBRARY)
  mark_as_advanced(GLOG_INCLUDE_DIR)

  if(NOT TARGET glog)
    add_library(glog INTERFACE)
    target_include_directories(glog INTERFACE ${GLOG_INCLUDE_DIR})
    target_link_libraries(glog INTERFACE ${GLOG_LIBRARY})
  endif(NOT TARGET glog)

  set(GLog_FOUND TRUE PARENT_SCOPE)
endfunction(_GLog_Import)

_GLog_Import()
