function(_FarmhashSource_Import)
  nn_include(ExternalSource)

  if(NOT DEFINED FARMHASH_URL)
    set(FARMHASH_URL "https://github.com/google/farmhash/archive/816a4ae622e964763ca0862d9dbd19324a1eaf45.tar.gz")
  endif(NOT DEFINED FARMHASH_URL)

  ExternalSource_Download(FARMHASH "${FARMHASH_URL}")

  set(FarmhashSource_DIR "${FARMHASH_SOURCE_DIR}" PARENT_SCOPE)
  set(FarmhashSource_FOUND TRUE PARENT_SCOPE)
endfunction(_FarmhashSource_Import)

_FarmhashSource_Import()
