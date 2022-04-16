function(_FFT2D_Import)
  nn_find_package(FFT2DSource QUIET)

  if(NOT FFT2DSource_FOUND)
    set(FFT2D_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT FFT2DSource_FOUND)

  if(NOT TARGET fft2d)
    nn_include(ExternalProject)
    add_extdirectory("${CMAKE_CURRENT_LIST_DIR}/FFT2D" fft2d)
  endif(NOT TARGET fft2d)

  set(FFT2D_FOUND TRUE PARENT_SCOPE)
endfunction(_FFT2D_Import)

_FFT2D_Import()
