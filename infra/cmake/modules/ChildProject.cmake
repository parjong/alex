function(ChildProject_AddAll)
  file(GLOB PROJECT_FILES
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            "*/CMakeLists.txt")

  foreach(PROJECT_FILE IN ITEMS ${PROJECT_FILES})
    get_filename_component(PROJECT_DIR ${PROJECT_FILE} DIRECTORY)
    add_subdirectory(${PROJECT_DIR})
  endforeach(PROJECT_FILE)
endfunction(ChildProject_AddAll)
