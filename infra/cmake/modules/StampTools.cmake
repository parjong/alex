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

function(Stamp_Remove_Unless STAMP_FILE COND)
  if(NOT COND)
    # Remove invalid STAMP
    if(EXISTS "${STAMP_FILE}")
      file(REMOVE "${STAMP_FILE}")
    endif(EXISTS "${STAMP_FILE}")
  endif(NOT COND)
endfunction(Stamp_Remove_Unless)

function(Stamp_Create STAMP_FILE CONTENT)
  file(WRITE "${STAMP_FILE}" "${CONTENT}")
endfunction(Stamp_Create)
