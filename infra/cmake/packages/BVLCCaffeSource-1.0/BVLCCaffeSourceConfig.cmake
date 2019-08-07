function(_Import)
  alex_include(ExternalSource)
  alex_include(AlexTools)

  alex_3rdparty_download(PACKAGE BVLCCaffe VERSION 1.0)

  set(BVLCCaffeSource_DIR "${BVLCCaffe_DIR}" PARENT_SCOPE)
  set(BVLCCaffeSource_FOUND TRUE PARENT_SCOPE)
endfunction(_Import)

_Import()
