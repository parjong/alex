set(TVM_PREFIX /usr CACHE PATH "...")
set(DMLC_PREFIX /usr CACHE PATH "...")

add_executable(tvm-sample sample.cpp)
target_include_directories(tvm-sample PRIVATE
  ${DMLC_PREFIX}/include
  ${TVM_PREFIX}/include
  ${TVM_PREFIX}/include/HalideIR
)
target_link_libraries(tvm-sample PUBLIC
  ${TVM_PREFIX}/lib/libnnvm_compiler.so
  ${TVM_PREFIX}/lib/libtvm_topi.so
  ${TVM_PREFIX}/lib/libtvm.so
  ${DMLC_PREFIX}/lib/libdmlc.a
)

add_test(tvm-test tvm-sample)
