function(Stamp_Check VAR STAMP_FILE EXPECTED)
  if(EXISTS "${STAMP_FILE}")
    file(READ "${STAMP_FILE}" CURRENT)

    if(EXPECTED STREQUAL CURRENT)
      set(${VAR} TRUE PARENT_SCOPE)
      return()
    endif(EXPECTED STREQUAL CURRENT)
  endif(EXISTS "${STAMP_FILE}")

  set(${VAR} FALSE PARENT_SCOPE)
endfunction(Stamp_Check)
