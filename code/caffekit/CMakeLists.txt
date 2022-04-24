# TODO Support automatic module ON/OFF
alex_find_package(BVLCCaffeSource EXACT 1.0 REQUIRED)
alex_find_package(Protobuf REQUIRED)

file(GLOB_RECURSE SRCS "src/*.cpp")

Protobuf_Generate(CAFFE_PROTO
  SOURCE_DIR ${BVLCCaffeSource_DIR}/src
  OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/gen
  FILES caffe/proto/caffe.proto
)

add_executable(caffekit ${SRCS} ${CAFFE_PROTO_SOURCES})
target_include_directories(caffekit PRIVATE ${CAFFE_PROTO_INCLUDE_DIRS})
target_link_libraries(caffekit PRIVATE ${CAFFE_PROTO_LIBRARIES})
target_link_libraries(caffekit PRIVATE cli)
