add_subdirectory(lib)

include_directories(${CANA_PATH}/inc lib)
add_compile_options(-std=c++11)

add_library(canaext_lua SHARED
  src/app.cpp
  src/loader.cpp
  src/entry.cpp
)

add_dependencies(canaext_lua pepper_interop)
target_link_libraries(canaext_lua pepper_interop boost_system boost_filesystem)

install(TARGETS canaext_lua DESTINATION ext/lua/binder)
