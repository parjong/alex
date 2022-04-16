function(_GEMMLowpSource_Import)
  nn_include(ExternalSource)

  if(NOT DEFINED GEMMLOWP_URL)
    set(GEMMLOWP_URL "https://mirror.bazel.build/github.com/google/gemmlowp/archive/7c7c744640ddc3d0af18fb245b4d23228813a71b.zip")
  endif(NOT DEFINED GEMMLOWP_URL)

  ExternalSource_Download(GEMMLOWP "${GEMMLOWP_URL}")

  set(GEMMLowpSource_DIR "${GEMMLOWP_SOURCE_DIR}" PARENT_SCOPE)
  set(GEMMLowpSource_FOUND TRUE PARENT_SCOPE)
endfunction(_GEMMLowpSource_Import)

_GEMMLowpSource_Import()
