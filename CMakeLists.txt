cmake_minimum_required(VERSION 3.2)

project(alex)

set(ALEX_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR} CACHE INTERNAL "top-level source directory")
set(ALEX_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "top-level binrary directory")

macro(alex_include PREFIX)
  include("${ALEX_PROJECT_SOURCE_DIR}/infra/cmake/modules/${PREFIX}.cmake")
endmacro(alex_include)

enable_testing()

add_subdirectory(code)
