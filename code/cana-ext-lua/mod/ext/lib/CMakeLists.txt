cmake_minimum_required(VERSION 2.8.8)

project(pepper-libs)

###
### Setup
###
enable_testing()

include_directories(".")

add_compile_options(-std=c++11 -fPIC)

###
### Testing
###
add_library(pepper_testing_main pepper/testing/main.cpp)

add_executable(sample_testing pepper/testing.sample.cpp)

target_link_libraries(sample_testing pepper_testing_main)

###
### Fun [Build & Test]
###
add_executable(test_pepper_fun pepper/fun.test.cpp)

target_link_libraries(test_pepper_fun pepper_testing_main)

add_test(test_pepper_fun test_pepper_fun)

###
### Mem [Build & Test]
###
add_executable(test_pepper_mem pepper/mem.test.cpp)

target_link_libraries(test_pepper_mem pepper_testing_main)

add_test(test_pepper_mem test_pepper_mem)

###
### Maybe [Build & Test]
###
add_executable(test_pepper_maybe pepper/maybe.test.cpp)

target_link_libraries(test_pepper_maybe pepper_testing_main)

add_test(test_pepper_maybe test_pepper_maybe)

###
### Stream [Build & Test]
###
add_executable(test_pepper_stream pepper/stream.test.cpp)

target_link_libraries(test_pepper_stream pepper_testing_main)

add_test(test_pepper_stream test_pepper_stream)

###
### Collection [Build & Test]
###
add_executable(test_pepper_collection pepper/collection.test.cpp)

target_link_libraries(test_pepper_collection pepper_testing_main)

add_test(test_pepper_collection test_pepper_collection)

###
### Array [Build & Test]
###
add_executable(test_pepper_array pepper/array.test.cpp)

target_link_libraries(test_pepper_array pepper_testing_main)

add_test(test_pepper_array test_pepper_array)

###
### Vector [Build & Test]
###
add_executable(test_pepper_vector pepper/vector.test.cpp)

target_link_libraries(test_pepper_vector pepper_testing_main)

add_test(test_pepper_vector test_pepper_vector)

###
### Dict [Build & Test]
###
add_executable(test_pepper_dict pepper/dict.test.cpp)

target_link_libraries(test_pepper_dict pepper_testing_main)

add_test(test_pepper_dict test_pepper_dict)

###
### Bucket [Build & Test]
###
add_executable(test_pepper_bucket pepper/bucket.test.cpp)

target_link_libraries(test_pepper_bucket pepper_testing_main)

add_test(test_pepper_bucket test_pepper_bucket)

###
### Optional [Build & Test]
###
add_executable(test_pepper_optional pepper/optional.test.cpp)

target_link_libraries(test_pepper_optional pepper_testing_main)

add_test(test_pepper_optional test_pepper_optional)

###
### LINQ [Build & Test]
###
add_executable(test_pepper_linq pepper/linq.test.cpp)

target_link_libraries(test_pepper_linq pepper_testing_main)

add_test(test_pepper_linq test_pepper_linq)

###
### View [Build & Test]
###
add_executable(test_pepper_view pepper/view.test.cpp)

target_link_libraries(test_pepper_view pepper_testing_main)

add_test(test_pepper_view test_pepper_view)

###
### Delegate [Build & Test]
###
add_executable(test_pepper_delegate pepper/delegate.test.cpp)

target_link_libraries(test_pepper_delegate pepper_testing_main)

add_test(test_pepper_delegate test_pepper_delegate)

###
### Filter [Build & Test]
###
add_executable(test_pepper_filter pepper/filter.test.cpp)

target_link_libraries(test_pepper_filter pepper_testing_main)

add_test(test_pepper_filter test_pepper_filter)

###
### Event [Build & Test]
###
add_executable(test_pepper_event pepper/event.test.cpp)

target_link_libraries(test_pepper_event pepper_testing_main)

add_test(test_pepper_event test_pepper_event)

###
### Random [Build & Test]
###
add_library(pepper_random
  pepper/random/number/head/object.cpp
  pepper/random/number/data/object.cpp
  pepper/random/number/object.cpp
)

add_executable(test_pepper_random pepper/random.test.cpp)

target_link_libraries(test_pepper_random
  pepper_testing_main
  pepper_random
)

add_test(test_pepper_random test_pepper_random)

###
### JPATH [Build & Test]
###
add_library(pepper_jpath
  pepper/jpath/object.cpp
  pepper/jpath/root/node.cpp
  pepper/jpath/named/node.cpp
  pepper/jpath/indexed/node.cpp
)

add_executable(test_pepper_jpath
  pepper/jpath.test.cpp
)

target_link_libraries(test_pepper_jpath
  pepper_testing_main
  pepper_jpath
)

add_test(test_pepper_jpath test_pepper_jpath)

###
### JIMAGE [Build & Test]
###
add_library(pepper_jimage
  pepper/jimage/object.cpp
)

add_executable(test_pepper_jimage
  pepper/jimage.test.cpp
)

target_link_libraries(test_pepper_jimage
  pepper_testing_main
  pepper_jimage
)

add_test(test_pepper_jimage test_pepper_jimage)

###
### JVIEW [Build & Test]
###
add_library(pepper_jview
  pepper/jview/fld.cpp
  pepper/jview/num/fld.cpp
  pepper/jview/num/reader.cpp
  pepper/jview/str/fld.cpp
  pepper/jview/str/reader.cpp
  pepper/jview/seq/fld.cpp
  pepper/jview/seq/reader.cpp
  pepper/jview/obj.cpp
)

target_link_libraries(pepper_jview
  pepper_jimage
  pepper_jpath
)

add_executable(test_pepper_jview
  pepper/jview.test.cpp
)

target_link_libraries(test_pepper_jview
  pepper_testing_main
  pepper_jview
)

add_test(test_pepper_jview test_pepper_jview)

###
### JSONCPP [Build & Test]
###
add_library(pepper_jsoncpp
  pepper/jsoncpp/path/object.cpp
  pepper/jsoncpp/path/root/accessor.cpp
  pepper/jsoncpp/path/named/accessor.cpp
  pepper/jsoncpp/path/indexed/accessor.cpp
  pepper/jsoncpp/path/make.cpp
  pepper/jsoncpp/image/accessor.cpp
  pepper/jsoncpp/image/cref/accessor.cpp
  pepper/jsoncpp/image/value/accessor.cpp
  pepper/jsoncpp/image/object.cpp
)

target_link_libraries(pepper_jsoncpp
  pepper_jimage
  pepper_jpath
  jsoncpp
)

add_executable(test_pepper_jsoncpp
  pepper/jsoncpp.test.cpp
)

target_link_libraries(test_pepper_jsoncpp
  pepper_testing_main
  pepper_jsoncpp
  pepper_jview
)

add_test(test_pepper_jsoncpp test_pepper_jsoncpp)

###
### JSON [Build & Test]
###
add_library(pepper_json
  pepper/json/cursor/rooted/accessor.cpp
  pepper/json/cursor/indexed/accessor.cpp
  pepper/json/cursor/named/accessor.cpp
  pepper/json/type/meta.cpp
  pepper/json/type/num/value.cpp
  pepper/json/type/num/field.cpp
  pepper/json/type/str/value.cpp
  pepper/json/type/str/field.cpp
  pepper/json/type/obj/value.cpp
  pepper/json/utils.cpp
)

target_link_libraries(pepper_json jsoncpp)

add_executable(test_pepper_json
  pepper/json.test.cpp
)

target_link_libraries(test_pepper_json
  pepper_testing_main
  pepper_json
  pepper_logging
  pepper_fmt
)

add_test(test_pepper_json test_pepper_json)

###
### Pathname [Build & Test]
###
add_library(pepper_pathname
  pepper/pathname/base.cpp
  pepper/pathname/glob.cpp
)

target_link_libraries(pepper_pathname
  boost_system
  boost_filesystem
)

add_executable(test_pepper_pathname
  pepper/pathname.test.cpp
)

target_link_libraries(test_pepper_pathname
  pepper_testing_main
  pepper_pathname
)

add_test(test_pepper_pathname test_pepper_pathname)

###
### Fs [Build & Test]
###
add_library(pepper_fs
  pepper/fs/sys/service.cpp
  pepper/fs/sys/file/service.cpp
  pepper/fs/collect.cpp
)

target_link_libraries(pepper_fs
  boost_system
  boost_filesystem
)

add_executable(test_pepper_fs pepper/fs.test.cpp)

target_link_libraries(test_pepper_fs
  pepper_testing_main
  pepper_fs
)

add_test(test_pepper_fs test_pepper_fs)

###
### Env [Build & Test]
###
add_library(pepper_env
  pepper/env/reader.cpp
  pepper/env/system/object.cpp
  pepper/env/system/setter/spec.cpp
)

add_executable(test_pepper_env pepper/env.test.cpp)

target_link_libraries(test_pepper_env
  pepper_testing_main
  pepper_env
)

add_test(test_pepper_env test_pepper_env)

###
### Attr [Build & Test]
###
add_executable(test_pepper_attr pepper/attr.test.cpp)

target_link_libraries(test_pepper_attr pepper_testing_main)

add_test(test_pepper_attr test_pepper_attr)

###
### Exn [Build & Test]
###
add_executable(test_pepper_exn pepper/exn.test.cpp)

target_link_libraries(test_pepper_exn
  pepper_testing_main
  pepper_fmt
)

###
### Fmt [Build & Test]
###
add_library(pepper_fmt pepper/fmt/base.cpp)

add_executable(test_pepper_fmt pepper/fmt.test.cpp)

target_link_libraries(test_pepper_fmt
  pepper_testing_main
  pepper_fmt
)

add_test(test_pepper_fmt test_pepper_fmt)

###
### Interop [Build & Test]
###
find_package(Lua51 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

add_library(pepper_interop
  pepper/interop/lua51/code/string/loader.cpp
  pepper/interop/lua51/code/stream/loader.cpp
  pepper/interop/lua51/binding/object.cpp
  pepper/interop/lua51/binding/loader.cpp
  pepper/interop/lua51/function/internal/loader.cpp
  pepper/interop/lua51/function/external/loader.cpp
  pepper/interop/lua51/heap/object.cpp
  pepper/interop/lua51/stack/accessor.cpp
  pepper/interop/lua51/stack/object.cpp
  pepper/interop/lua51/binder/object.cpp
  pepper/interop/lua51/context.cpp
  pepper/interop/lua51/runtime.cpp
)

target_link_libraries(pepper_interop ${LUA_LIBRARIES})

add_executable(test_pepper_interop pepper/interop.test.cpp)

target_link_libraries(test_pepper_interop
  pepper_testing_main
  pepper_interop
)

add_test(test_pepper_interop test_pepper_interop)

###
### Logging [Build & Test]
###
add_library(pepper_logging
  pepper/logging/logger.cpp
  pepper/logging/utils.cpp
)

target_link_libraries(pepper_logging
  boost_system
  boost_filesystem
  log4cxx
  pepper_fmt
)

add_executable(test_pepper_logging pepper/logging.test.cpp)

target_link_libraries(test_pepper_logging
  pepper_testing_main
  pepper_logging
)

add_test(test_pepper_logging test_pepper_logging)

###
### Cmdline [Build & Test]
###
add_library(pepper_cmdline
  pepper/cmdline/desc.cpp
  pepper/cmdline/option/desc.cpp
  pepper/cmdline/parser.cpp
)

add_executable(test_pepper_cmdline
  pepper/cmdline.test.cpp
)

target_link_libraries(test_pepper_cmdline
  pepper_testing_main
  pepper_cmdline
)

add_test(test_pepper_cmdline test_pepper_cmdline)

###
### Appfw [Build & Test]
###
add_library(pepper_appfw
  pepper/appfw/apps/basic/service.cpp
  pepper/appfw/apps/basic/desc.cpp
  pepper/appfw/apps/nested/command.cpp
  pepper/appfw/apps/nested/desc.cpp
  pepper/appfw/cli/host.cpp
  pepper/appfw/cli/unit.cpp
  pepper/appfw/cli/option/set.cpp
  pepper/appfw/cli/command/set.cpp
  pepper/appfw/cli/service/impl.cpp
  pepper/appfw/cli/service/cmdline/impl.cpp
  pepper/appfw/cli/service/exitcode/impl.cpp
)

target_link_libraries(pepper_appfw
  pepper_fmt
  pepper_cmdline
)

add_executable(sample_appfw pepper/appfw.sample.cpp)

target_link_libraries(sample_appfw pepper_appfw)

add_executable(test_pepper_appfw pepper/appfw.test.cpp)

target_link_libraries(test_pepper_appfw
  pepper_testing_main
  pepper_appfw
  pepper_logging
  pepper_fmt
)

add_test(test_pepper_appfw test_pepper_appfw)
