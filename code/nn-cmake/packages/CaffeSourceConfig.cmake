function(_CaffeSource_Import)
  nn_include(ExternalSource)

  if(NOT DEFINED CAFFE_URL)
    set(CAFFE_URL https://github.com/BVLC/caffe/archive/1.0.tar.gz)
  endif(NOT DEFINED CAFFE_URL)

  ExternalSource_Download(CAFFE "${CAFFE_URL}")

  set(CaffeSource_DIR "${CAFFE_SOURCE_DIR}" PARENT_SCOPE)
  set(CaffeSource_FOUND TRUE PARENT_SCOPE)
endfunction(_CaffeSource_Import)

_CaffeSource_Import()
