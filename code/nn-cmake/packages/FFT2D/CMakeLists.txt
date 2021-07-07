add_library(fft2d STATIC "${FFT2DSource_DIR}/fftsg.c")
set_target_properties(fft2d PROPERTIES POSITION_INDEPENDENT_CODE ON)
