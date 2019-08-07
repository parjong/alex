function(_GoogleTestSource_Download)
  alex_include(ExternalSource)
  alex_include(AlexTools)

  alex_3rdparty_download(PACKAGE GoogleTest VERSION 1.8.0)

  set(GoogleTestSource_DIR "${GoogleTest_DIR}" PARENT_SCOPE)
  set(GoogleTestSource_FOUND TRUE PARENT_SCOPE)
endfunction(_GoogleTestSource_Download)

_GoogleTestSource_Download()
