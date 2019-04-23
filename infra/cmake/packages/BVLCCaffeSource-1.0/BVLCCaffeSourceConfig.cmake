function(_Import)
  alex_include(ExternalSource)

  set(BVLCCAFFE_URL "https://github.com/BVLC/caffe/archive/1.0.tar.gz" CACHE STRING "BVLC Caffe 1.0 source archive URL")

  ExternalSource_Download(BVLCCAFFE DIRNAME BVLCCAFFE-1.0 URL "${BVLCCAFFE_URL}")

  set(BVLCCaffeSource_DIR "${BVLCCAFFE_SOURCE_DIR}" PARENT_SCOPE)
  set(BVLCCaffeSource_FOUND TRUE PARENT_SCOPE)
endfunction(_Import)

_Import()
