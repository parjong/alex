add_library(canaext_native SHARED
  native/binder/loader.cpp
  native/binder/entry.cpp
)

target_link_libraries(canaext_native boost_system boost_filesystem)

add_library(canaext_native_echo SHARED
  native/apps/echo/entry.cpp
)

install(TARGETS canaext_native DESTINATION ext/native/binder)
install(TARGETS canaext_native_echo
        DESTINATION ext/native/apps/echo)
install(FILES native/apps/echo/plugin.json
        DESTINATION ext/native/apps/echo)
