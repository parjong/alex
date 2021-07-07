function(_GEMMLowp_Import)
  nn_include(ExternalSource)

  nn_find_package(GEMMLowpSource QUIET)

  if(NOT GEMMLowpSource_FOUND)
    set(GEMMLowp_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT GEMMLowpSource_FOUND)

  if(NOT TARGET gemmlowp)
    add_library(gemmlowp INTERFACE)
		target_include_directories(gemmlowp INTERFACE "${GEMMLowpSource_DIR}")
		target_compile_definitions(gemmlowp INTERFACE GEMMLOWP_ALLOW_SLOW_SCALAR_FALLBACK)

    message(STATUS "Found GEMMLowp (include: ${GEMMLowpSource_DIR})")
  endif(NOT TARGET gemmlowp)

  set(GEMMLowp_FOUND TRUE PARENT_SCOPE)
endfunction(_GEMMLowp_Import)

_GEMMLowp_Import()
