# TODO Support automatic module ON/OFF
alex_find_package(BVLCCaffeSource EXACT 1.0 REQUIRED)
# TODO Use alex_find_package later
find_package(Protobuf MODULE REQUIRED)

file(GLOB_RECURSE SRCS "src/*.cpp")

# TODO Make below as a reusable function
set(PROTO_SRCDIR "${BVLCCaffeSource_DIR}/src")
set(PROTO_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${PROTO_OUTDIR})

unset(GEN_COMMAND)
list(APPEND GEN_COMMAND "${PROTOBUF_PROTOC_EXECUTABLE}")
list(APPEND GEN_COMMAND --proto_path="${PROTO_SRCDIR}")
list(APPEND GEN_COMMAND --cpp_out="${PROTO_OUTDIR}")
list(APPEND GEN_COMMAND "${PROTO_SRCDIR}/caffe/proto/caffe.proto")

add_custom_command(
  OUTPUT "${PROTO_OUTDIR}/caffe/proto/caffe.pb.h" "${PROTO_OUTDIR}/caffe/proto/caffe.pb.cc"
  COMMAND ${GEN_COMMAND}
  DEPENDS "${PROTO_SRCDIR}/caffe/proto/caffe.proto"
)

set(Generated_INCLUDE_DIR "${PROTO_OUTDIR}")
set(Generated_SRCS "${PROTO_OUTDIR}/caffe/proto/caffe.pb.cc")

add_executable(caffekit ${SRCS} ${Generated_SRCS})
target_include_directories(caffekit PRIVATE ${Generated_INCLUDE_DIR})
target_include_directories(caffekit PRIVATE ${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(caffekit PRIVATE ${PROTOBUF_LIBRARIES})
