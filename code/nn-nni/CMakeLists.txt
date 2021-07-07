# TODO Remove this
return()

add_library(nni-core INTERFACE)
target_include_directories(nni-core INTERFACE include)
target_link_libraries(nni-core INTERFACE tensor)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(nni ${SOURCES})
set_target_properties(nni PROPERTIES CXX_STANDARD 14)
target_link_libraries(nni nni-core)
target_link_libraries(nni dl)

nn_find_package(Caffe QUIET)

if(Caffe_FOUND)
  add_library(nni-caffe SHARED backends/caffe/Caffe.cpp)
  set_target_properties(nni-caffe PROPERTIES CXX_STANDARD 14)
  target_link_libraries(nni-caffe nni-core)
  target_link_libraries(nni-caffe caffe)
endif(Caffe_FOUND)

nn_find_package(TensorflowLite QUIET)

if(TensorflowLite_FOUND)
  add_library(nni-tflite SHARED backends/tflite/TensorflowLite.cpp)
  set_target_properties(nni-tflite PROPERTIES CXX_STANDARD 14)
  target_link_libraries(nni-tflite nni-core)
  target_link_libraries(nni-tflite tensorflow-lite)
endif(TensorflowLite_FOUND)

add_library(nni-show SHARED actions/builtin/Show.cpp)
set_target_properties(nni-show PROPERTIES CXX_STANDARD 14)
target_link_libraries(nni-show nni-core)

find_package(HDF5 COMPONENTS CXX HL QUIET)

if(HDF5_FOUND)
  add_library(hdf5 INTERFACE)
  target_include_directories(hdf5 INTERFACE ${HDF5_INCLUDE_DIRS})
  target_compile_options(hdf5 INTERFACE ${HDF5_DEFINITIONS})
  target_link_libraries(hdf5 INTERFACE ${HDF5_LIBRARIES})
  target_link_libraries(hdf5 INTERFACE ${HDF5_HL_LIBRARIES})
  target_link_libraries(hdf5 INTERFACE ${HDF5_CXX_LIBRARIES})
  target_link_libraries(hdf5 INTERFACE ${HDF5_CXX_HL_LIBRARIES})

  add_library(nni-hdf5-export SHARED actions/HDF5/Export.cpp)
  set_target_properties(nni-hdf5-export PROPERTIES CXX_STANDARD 14)
  target_link_libraries(nni-hdf5-export hdf5)
  target_link_libraries(nni-hdf5-export nni-core)

  add_library(nni-hdf5-import SHARED actions/HDF5/Import.cpp)
  set_target_properties(nni-hdf5-import PROPERTIES CXX_STANDARD 14)
  target_link_libraries(nni-hdf5-import hdf5)
  target_link_libraries(nni-hdf5-import nni-core)
endif(HDF5_FOUND)
