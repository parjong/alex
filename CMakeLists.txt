cmake_minimum_required(VERSION 3.2)

project(alex)

set(ALEX_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR} CACHE INTERNAL "top-level source directory")
set(ALEX_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "top-level binrary directory")
set(ALEX_OVERLAY_DIR "${ALEX_PROJECT_BINARY_DIR}/overlay" CACHE INTERNAL "overlay directory")

include(infra/cmake/alex.cmake)

# Set standard C++ 11 (without extension) as the default configuration
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_PREFIX_PATH "${ALEX_OVERLAY_DIR}")

enable_testing()

add_subdirectory(code)
