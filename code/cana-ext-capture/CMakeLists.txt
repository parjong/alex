# TODO Enable this project
return()

cmake_minimum_required (VERSION 2.8.8)

project(capture)

if(NOT DEFINED CANA_PATH)
  set(CANA_PATH $ENV{CANA_PATH})
endif(NOT DEFINED CANA_PATH)

if(NOT DEFINED CANA_PATH)
  message(FATAL_ERROR "CANA_PATH should be specified")
endif(NOT DEFINED CANA_PATH)

include_directories(${CANA_PATH}/inc)

add_compile_options(-std=c++14)

add_library(canaapp_capture SHARED
  src/lowering/context.cpp
  src/lowering/rule.cpp
  src/lowering/engine.cpp
  src/parsing/context.cpp
  src/parsing/rule.cpp
  src/parsing/engine.cpp
  src/action.cpp
  src/app.cpp
  src/entry.cpp
)

install(TARGETS canaapp_capture DESTINATION app)
install(FILES src/plugin.json DESTINATION app)
