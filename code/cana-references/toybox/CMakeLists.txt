cmake_minimum_required (VERSION 2.8.11)

project (toybox)

find_package (LLVM REQUIRED CONFIG)

message (STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message (STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message (STATUS "Using LLVM_DEFINITIONS : ${LLVM_DEFINITIONS}")

include_directories (${LLVM_INCLUDE_DIRS})

add_definitions (-std=c++11)
add_definitions (-fno-rtti)
add_definitions (${LLVM_DEFINITIONS})

llvm_map_components_to_libnames (llvm_libs all)

###
enable_testing()

###
add_subdirectory (hiberlite)

include_directories (src/)
include_directories (hiberlite/include)

###
find_package (GTest REQUIRED)

###
list (APPEND EMIT_SOURCES src/context.cc)
list (APPEND EMIT_SOURCES src/emit/command.cc)
list (APPEND EMIT_SOURCES src/emit/failure.cc)
list (APPEND EMIT_SOURCES src/emit/code.cc)
list (APPEND EMIT_SOURCES src/emit/emit.cc)
list (APPEND EMIT_SOURCES src/command_runner.cc)

add_library (emit ${EMIT_SOURCES})

target_link_libraries (emit hiberlite)

###
list (APPEND QUERY_SOURCES src/query/mode.cc)
list (APPEND QUERY_SOURCES src/query/list_file.cc)
list (APPEND QUERY_SOURCES src/query/list_command.cc)
list (APPEND QUERY_SOURCES src/query/list_failure.cc)
list (APPEND QUERY_SOURCES src/query/show_file.cc)
list (APPEND QUERY_SOURCES src/query/show_command.cc)
list (APPEND QUERY_SOURCES src/query/exec.cc)
list (APPEND QUERY_SOURCES src/query/query.cc)

add_executable (query ${QUERY_SOURCES})

target_link_libraries (query emit)

install (TARGETS query DESTINATION bin)

###
list (APPEND SOURCES src/terminator.cc)
list (APPEND SOURCES src/build/plugin.cc)
list (APPEND SOURCES src/build/gcc_arity.cc)
list (APPEND SOURCES src/build/gcc_option.cc)
list (APPEND SOURCES src/build/gcc_options.cc)
list (APPEND SOURCES src/build/gcc_utils.cc)
list (APPEND SOURCES src/build/gcc_parser.cc)
list (APPEND SOURCES src/build/gcc_plugin.cc)
list (APPEND SOURCES src/build/FrontendActionRunner.cc)
list (APPEND SOURCES src/build/tracee.cc)
list (APPEND SOURCES src/build/tracer.cc)
list (APPEND SOURCES src/build/record_tracer.cc)
list (APPEND SOURCES src/build/monitor.cc)
list (APPEND SOURCES src/build.cc)

add_library (trace ${SOURCES})

target_link_libraries (trace emit)

target_link_libraries (trace clangTooling)
target_link_libraries (trace clangFrontend)
target_link_libraries (trace clangDriver)
target_link_libraries (trace clangParse)
target_link_libraries (trace clangSema)
target_link_libraries (trace clangSerialization)
target_link_libraries (trace clangAnalysis)
target_link_libraries (trace clangRewriteFrontend)
target_link_libraries (trace clangRewrite)
target_link_libraries (trace clangCodeGen)
target_link_libraries (trace clangEdit)
target_link_libraries (trace clangAST)
target_link_libraries (trace clangLex)
target_link_libraries (trace clangBasic)

target_link_libraries (trace ${llvm_libs})

###
add_executable (build src/build.cc)

target_link_libraries (build trace)

install (TARGETS build DESTINATION bin)

###
list (APPEND TESTS src/build-test.cc)

add_executable (build-test ${TESTS})

target_link_libraries (build-test gtest)
target_link_libraries (build-test pthread)
target_link_libraries (build-test trace)

###
add_executable (analyze src/CFG.cc src/analyze.cc)

target_link_libraries (analyze trace)

install (TARGETS analyze DESTINATION bin)


#
#
#
add_test(run-build-test build-test)
