function(_Caffe_Build)
  nn_find_package(CaffeSource QUIET)

  if(NOT CaffeSource_FOUND)
    set(Caffe_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT CaffeSource_FOUND)

  nn_find_package(CaffeProto QUIET)

  if(NOT CaffeProto_FOUND)
    set(Caffe_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT CaffeProto_FOUND)

  nn_find_package(Atlas QUIET)

  if(NOT Atlas_FOUND)
    set(Caffe_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT Atlas_FOUND)

  nn_find_package(GLog QUIET)
  
  if(NOT GLog_FOUND)
    set(Caffe_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT GLog_FOUND)

  nn_find_package(GFlags QUIET)

  if(NOT GFlags_FOUND)
    set(Caffe_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT GFlags_FOUND)

  find_package(Boost 1.54 QUIET COMPONENTS system thread filesystem)

  if(NOT Boost_FOUND)
    set(Caffe_FOUND FALSE PARENT_SCOPE)
    return() 
  endif(NOT Boost_FOUND)

  find_package(HDF5 QUIET COMPONENTS HL)

  if(NOT HDF5_FOUND)
    set(Caffe_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT HDF5_FOUND)

  if(NOT TARGET caffe)
    nn_include(ExternalProject)
    add_extdirectory("${CMAKE_CURRENT_LIST_DIR}/Caffe" caffe)
  endif(NOT TARGET caffe)
endfunction(_Caffe_Build)

_Caffe_Build()
