cmake_minimum_required(VERSION 3.2)

project(alex)

set(ALEX_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR} CACHE INTERNAL "top-level source directory")
set(ALEX_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "top-level binrary directory")

macro(alex_include PREFIX)
  include("${ALEX_PROJECT_SOURCE_DIR}/infra/cmake/modules/${PREFIX}.cmake")
endmacro(alex_include)

macro(alex_find_package PREFIX)
  find_package(${PREFIX} CONFIG NO_DEFAULT_PATH PATHS "${ALEX_PROJECT_SOURCE_DIR}/infra/cmake/packages" ${ARGN})
endmacro(alex_find_package)

# Set standard C++ 11 (without extension) as the default configuration
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(code)
