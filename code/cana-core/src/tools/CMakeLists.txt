include_directories(.)

add_library(cana SHARED
  cana/logging/manager.cpp
  cana/logging/point.cpp
  cana/fwklib/packaging/fs/package.cpp
  cana/fwklib/packaging/fs/storage.cpp
  cana/fwklib/packaging/fs/logstream.cpp
  cana/fwklib/packaging/fs/service.cpp
  cana/core/storage.cpp
  cana/core/binder/catalog.cpp
  cana/core/app/tracker.cpp
  cana/core/app/store.cpp
  cana/corelib/log/text/file.cpp
  cana/corelib/log/text/stream.cpp
  cana/corelib/log/text/factory.cpp
  cana/corelib/log/text/backend.cpp
  cana/corelib/binding/json/package.cpp
  cana/corelib/binding/json/binder.cpp
  cana/corelib/loading/json/package.cpp
  cana/corelib/loading/json/loader.cpp
  cana/sys/object.cpp
)

target_link_libraries(cana dl boost_system boost_filesystem)

add_library(cana_rt SHARED
  cana/rt/preload/hook.cpp
  cana/rt/preload/record.cpp
  cana/rt/preload/arg.cpp
  cana/rt/preload/env.cpp
  cana/rt/preload/process.cpp
)

target_link_libraries(cana_rt cana boost_system boost_filesystem)

install(TARGETS cana cana_rt DESTINATION lib)


