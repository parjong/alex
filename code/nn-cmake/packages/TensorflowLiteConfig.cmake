function(_TensorflowLite_Build)
  nn_find_package(TensorflowSource QUIET)

  if(NOT TensorflowSource_FOUND)
    set(TensorflowLite_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT TensorflowSource_FOUND)

  nn_find_package(Flatbuffers QUIET)

  if(NOT Flatbuffers_FOUND)
    set(TensorflowLite_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT Flatbuffers_FOUND)

  nn_find_package(Eigen QUIET)

  if(NOT Eigen_FOUND)
    set(TensorflowLite_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT Eigen_FOUND)

  nn_find_package(Farmhash QUIET)

  if(NOT Farmhash_FOUND)
    set(TensorflowLite_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT Farmhash_FOUND)

  nn_find_package(GEMMLowp QUIET)

  if(NOT GEMMLowp_FOUND)
    set(TensorflowLite_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT GEMMLowp_FOUND)

  nn_find_package(FFT2D QUIET)

  if(NOT FFT2D_FOUND)
    set(TensorflowLite_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT FFT2D_FOUND)

  if(NOT TARGET tensorflow-lite)
    nn_include(ExternalProject)
    add_extdirectory("${CMAKE_CURRENT_LIST_DIR}/TensorflowLite" tflite)
  endif(NOT TARGET tensorflow-lite)

  set(TensorflowLite_FOUND TRUE PARENT_SCIPE)
endfunction(_TensorflowLite_Build)

_TensorflowLite_Build()
