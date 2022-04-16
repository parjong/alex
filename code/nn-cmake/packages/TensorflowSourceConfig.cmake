function(_TensorflowSource_Import)
  nn_include(ExternalSource)

  if(NOT DEFINED TENSORFLOW_URL)
    set(TENSORFLOW_URL "https://github.com/tensorflow/tensorflow/archive/v1.8.0.tar.gz")
  endif(NOT DEFINED TENSORFLOW_URL)

  ExternalSource_Download(TENSORFLOW "${TENSORFLOW_URL}")

  set(TensorflowSource_DIR "${TENSORFLOW_SOURCE_DIR}" PARENT_SCOPE)
  set(TensorflowSource_FOUND TRUE PARENT_SCOPE)
endfunction(_TensorflowSource_Import)

_TensorflowSource_Import()
