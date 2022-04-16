# TODO Enable this
return()

cmake_minimum_required (VERSION 2.8.8)

project (canaext_lua51)

if(NOT DEFINED CANA_PATH)
  set(CANA_PATH $ENV{CANA_PATH})
endif(NOT DEFINED CANA_PATH)

if(NOT DEFINED CANA_PATH)
  message(FATAL_ERROR "CANA_PATH should be specified")
endif(NOT DEFINED CANA_PATH)

add_subdirectory(mod)
