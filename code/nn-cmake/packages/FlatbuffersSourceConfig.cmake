function(_FlatbuffersSource_Import)
  nn_include(ExternalSource)

  if(NOT DEFINED FLATBUFFERS_URL)
    set(FLATBUFFERS_URL "https://github.com/google/flatbuffers/archive/v1.9.0.tar.gz")
  endif(NOT DEFINED FLATBUFFERS_URL)

  ExternalSource_Download(FLATBUFFERS "${FLATBUFFERS_URL}")

  set(FlatbuffersSource_DIR "${FLATBUFFERS_SOURCE_DIR}" PARENT_SCOPE)
  set(FlatbuffersSource_FOUND TRUE PARENT_SCOPE)
endfunction(_FlatbuffersSource_Import)

_FlatbuffersSource_Import()
