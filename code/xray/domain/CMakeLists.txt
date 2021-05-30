# "domain" libraries SHOULD BE a shared library
# in order to allow both "tracee" and "tracer" to share the same view.
add_library(xray-mydomain SHARED domain.example.cpp)
target_link_libraries(xray-mydomain PUBLIC xray-core)
target_include_directories(xray-mydomain PUBLIC include)
