function(_TensorFlowSource_Download)
  alex_include(ExternalSource)

  set(TENSORFLOW_URL
    "https://github.com/tensorflow/tensorflow/archive/v1.14.0.tar.gz" CACHE
    STRING "Google Test 1.8.0 source URL"
  )

  ExternalSource_Download(TENSORFLOW DIRNAME TENSORFLOW_URL-1.14.0 URL "${TENSORFLOW_URL}")

  # Set FALSE on download failure
  set(TensorFlowSource_DIR "${TENSORFLOW_SOURCE_DIR}" PARENT_SCOPE)
  set(TensorFlowSource_FOUND TRUE PARENT_SCOPE)
endfunction(_TensorFlowSource_Download)

_TensorFlowSource_Download()
