cmake_minimum_required (VERSION 2.8.8)

project (cana)

set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(inc)
add_compile_options(-std=c++11)

add_subdirectory(src)

install(DIRECTORY inc/ DESTINATION inc FILES_MATCHING PATTERN "*")
