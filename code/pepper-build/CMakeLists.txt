cmake_minimum_required(VERSION 2.8.8)

project(pepper_build)

### 
add_subdirectory(libs)

include_directories(libs)

###
### BUILD
###
add_compile_options(-std=c++11)

include_directories(".")
include_directories("src")

add_library(pepperbuild_adapter
  adapter/cmake/command.cpp
  adapter/cmake/spec.cpp
)

add_library(pepperbuild_core
  core/fwk/manager.cpp
  core/unit/name.cpp
  core/unit/desc.cpp
  core/unit/data.cpp
  core/unit/manifest/spec.cpp
  core/unit/pathname/root.cpp
  core/unit/op/build.cpp
  core/project/desc.cpp
  core/project/data.cpp
  core/project/manifest/spec.cpp
  core/project/pathname/root.cpp
  core/project/op/build.cpp
)

add_library(pepperbuild_native
  native/artifact/base.cpp
  native/toolchain/compile/gcc/instance.cpp
  native/toolchain/compile/gcc/factory.cpp
  native/toolchain/build/cmake/base.cpp
  native/toolchain/build/internal/base.cpp
  native/unit/lib/type.cpp
  native/unit/exe/type.cpp
)

target_link_libraries(pepperbuild_native pepperbuild_adapter)

# pepper
add_executable(pepper 
  src/main.cpp
  src/command/build.cpp
  src/cfg/ctxt.cpp
  src/cfg/spec.cpp
)

target_link_libraries(pepper
  pepperbuild_core
  pepperbuild_native
  pepper_env
  pepper_appfw
  pepper_pathname
  pepper_fs
  pepper_logging
  pepper_json
  jsoncpp
  log4cxx
  boost_system
  boost_filesystem
)

###
### TEST
###
#enable_testing()
