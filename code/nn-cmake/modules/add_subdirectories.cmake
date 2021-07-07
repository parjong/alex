function(add_subdirectories)
  file(GLOB PROJECT_FILES
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            "*/CMakeLists.txt")

  foreach(PROJECT_FILE IN ITEMS ${PROJECT_FILES})
    get_filename_component(PROJECT_DIR ${PROJECT_FILE} DIRECTORY)
    add_subdirectory(${PROJECT_DIR})
  endforeach(PROJECT_FILE)
endfunction(add_subdirectories)
