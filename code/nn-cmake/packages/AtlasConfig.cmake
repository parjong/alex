function(_Atlas_Import)
  list(APPEND Atlas_INCLUDE_SEARCH_PATHS /usr/include/atlas)
  list(APPEND Atlas_INCLUDE_SEARCH_PATHS /usr/include/atlas-base)
  list(APPEND Atlas_INCLUDE_SEARCH_PATHS $ENV{Atlas_ROOT_DIR})
  list(APPEND Atlas_INCLUDE_SEARCH_PATHS $ENV{Atlas_ROOT_DIR}/include)

  list(APPEND Atlas_LIB_SEARCH_PATHS /usr/lib/atlas)
  list(APPEND Atlas_LIB_SEARCH_PATHS /usr/lib/atlas-base)
  list(APPEND Atlas_LIB_SEARCH_PATHS $ENV{Atlas_ROOT_DIR})
  list(APPEND Atlas_LIB_SEARCH_PATHS $ENV{Atlas_ROOT_DIR}/lib)

  find_path(Atlas_CBLAS_INCLUDE_DIR   NAMES cblas.h   PATHS ${Atlas_INCLUDE_SEARCH_PATHS})
  find_path(Atlas_CLAPACK_INCLUDE_DIR NAMES clapack.h PATHS ${Atlas_INCLUDE_SEARCH_PATHS})

  find_library(Atlas_CBLAS_LIBRARY NAMES  ptcblas_r ptcblas cblas_r cblas       PATHS ${Atlas_LIB_SEARCH_PATHS})
  find_library(Atlas_BLAS_LIBRARY NAMES   atlas_r   atlas                       PATHS ${Atlas_LIB_SEARCH_PATHS})
  find_library(Atlas_LAPACK_LIBRARY NAMES lapack alapack_r alapack lapack_atlas atllapack PATHS ${Atlas_LIB_SEARCH_PATHS})

  set(LOOKED_FOR
      Atlas_CBLAS_INCLUDE_DIR
      Atlas_CLAPACK_INCLUDE_DIR

      Atlas_CBLAS_LIBRARY
      Atlas_BLAS_LIBRARY
      Atlas_LAPACK_LIBRARY
    )

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(Atlas DEFAULT_MSG ${LOOKED_FOR})

  if(NOT ATLAS_FOUND)
    set(Atlas_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT ATLAS_FOUND)

  set(Atlas_INCLUDE_DIR ${Atlas_CBLAS_INCLUDE_DIR} ${Atlas_CLAPACK_INCLUDE_DIR})
  set(Atlas_LIBRARIES ${Atlas_LAPACK_LIBRARY} ${Atlas_CBLAS_LIBRARY} ${Atlas_BLAS_LIBRARY})
  mark_as_advanced(${LOOKED_FOR})

  message(STATUS "Found Atlas (include: ${Atlas_CBLAS_INCLUDE_DIR} library: ${Atlas_BLAS_LIBRARY} lapack: ${Atlas_LAPACK_LIBRARY}")

  if(NOT TARGET atlas)
    add_library(atlas INTERFACE)
    target_include_directories(atlas INTERFACE ${Atlas_INCLUDE_DIR})
    target_link_libraries(atlas INTERFACE ${Atlas_LIBRARIES})
  endif(NOT TARGET atlas)

  set(Atlas_FOUND TRUE PARENT_SCOPE)
endfunction(_Atlas_Import)

_Atlas_Import()
