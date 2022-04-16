macro(add_extdirectory PATH PREFIX)
  add_subdirectory("${PATH}" "${NN_BINRARY_DIR}/externals/${PREFIX}")
endmacro(add_extdirectory)
