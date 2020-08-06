set(DEFAULT_VERSION "v200" CACHE STRING "Default version")

add_executable(example example.cpp)
target_compile_definitions(example PRIVATE DEFAULT_VERSION=${DEFAULT_VERSION})
