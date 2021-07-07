function(_FFT2DSource_Import)
  nn_include(ExternalSource)

  if(NOT DEFINED FFT2D_URL)
    set(FFT2D_URL http://www.kurims.kyoto-u.ac.jp/~ooura/fft.tgz)
  endif(NOT DEFINED FFT2D_URL)

  ExternalSource_Download(FFT2D "${FFT2D_URL}")

  set(FFT2DSource_DIR "${FFT2D_SOURCE_DIR}" PARENT_SCOPE)
  set(FFT2DSource_FOUND TRUE PARENT_SCOPE)
endfunction(_FFT2DSource_Import)

_FFT2DSource_Import()
