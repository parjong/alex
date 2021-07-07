cmake_minimum_required(VERSION 2.8)

project (capture)

add_definitions (-std=c++11)
include_directories (.)

#
# libdal.so Database Abstraction Layer
#
add_library(dal SHARED libdal/database.cc)

target_link_libraries (dal sqlite3)

#
# libbuild.so Build Database Object
#
add_library (build SHARED libbuild/build.cc)

target_link_libraries (build dal boost_regex)

#
# libscan.so
#
add_library (scan SHARED libscan/scanner.cc libscan/stream/vector.cc libscan/cursor.cc libscan/action/consume.cc libscan/action/match.cc libscan/action/registry.cc)

target_link_libraries (scan boost_regex)

#
# libcapture.so
#
add_library (capture SHARED libcapture/capture.cc libcapture/backend.cc)

target_link_libraries (capture build scan boost_system boost_filesystem)

#
# init_session
#
add_executable (init_session tools/init.cc)

target_link_libraries (init_session build)

#
# fini_session
#
add_executable (fini_session tools/fini.cc)

target_link_libraries (fini_session build)

