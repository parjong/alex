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
### Functional [Build & Test]
###
add_executable(test_pepper_functional pepper/functional.test.cpp)

target_link_libraries(test_pepper_functional pepper_testing_main)

add_test(test_pepper_functional test_pepper_functional)

###
### Maybe [Build & Test]
###
add_executable(test_pepper_maybe pepper/maybe.test.cpp)

target_link_libraries(test_pepper_maybe pepper_testing_main)

add_test(test_pepper_maybe test_pepper_maybe)

###
### Optional [Build & Test]
###
add_executable(test_pepper_optional pepper/optional.test.cpp)

target_link_libraries(test_pepper_optional pepper_testing_main)

add_test(test_pepper_optional test_pepper_optional)

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
### Multicast [Build & Test]
###
add_executable(test_pepper_multicast pepper/multicast.test.cpp)

target_link_libraries(test_pepper_multicast pepper_testing_main)

add_test(test_pepper_multicast test_pepper_multicast)

###
### Array [Build & Test]
###
add_executable(test_pepper_array pepper/array.test.cpp)

target_link_libraries(test_pepper_array pepper_testing_main)

add_test(test_pepper_array test_pepper_array)

###
### Vector [Build & Test]
###
add_executable(test_pepper_vector 
  pepper/vector.test.cpp
)

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
### ATTR [Build & Test]
###
add_executable(test_pepper_attr pepper/attr.test.cpp)

target_link_libraries(test_pepper_attr pepper_testing_main)

add_test(test_pepper_attr test_pepper_attr)

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
### ENV [Build & Test]
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
### FMT
###
add_library(pepper_fmt pepper/fmt/base.cpp)

add_executable(test_pepper_fmt pepper/fmt.test.cpp)

target_link_libraries(test_pepper_fmt
  pepper_testing_main
  pepper_fmt
)

add_test(test_pepper_fmt test_pepper_fmt)

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
### View [Build & Test]
###
add_executable(test_pepper_view pepper/view.test.cpp)

target_link_libraries(test_pepper_view pepper_testing_main)

add_test(test_pepper_view test_pepper_view)

###
### JSON [Build & Test]
###
add_library(pepper_json 
  pepper/json/cursor/root.cpp
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
  pepper/json/type/field.test.cpp
)

target_link_libraries(test_pepper_json 
  pepper_testing_main
  pepper_json 
  pepper_logging
  pepper_fmt
)

add_test(test_pepper_json test_pepper_json)

###
### Mem [Build & Test]
###
add_executable(test_pepper_mem pepper/mem.test.cpp)

target_link_libraries(test_pepper_mem pepper_testing_main)

add_test(test_pepper_mem test_pepper_mem)

###
### Exn [Build & Test]
###
add_executable(test_pepper_exn pepper/exn.test.cpp)

target_link_libraries(test_pepper_exn
  pepper_testing_main
  pepper_fmt
)

###
### Filesystem [Build & Test]
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
### LINQ [Build & Test]
###
add_executable(test_pepper_linq pepper/linq.test.cpp)

target_link_libraries(test_pepper_linq pepper_testing_main)

add_test(test_pepper_linq test_pepper_linq)

###
### CMDLINE [Build & Test]
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
### Application Framework [Build & Test]
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

target_link_libraries(sample_appfw
  pepper_appfw
)

add_executable(test_pepper_appfw pepper/appfw.test.cpp)

target_link_libraries(test_pepper_appfw
  pepper_testing_main
  pepper_appfw
  pepper_logging
  pepper_fmt
)

add_test(test_pepper_appfw test_pepper_appfw)
