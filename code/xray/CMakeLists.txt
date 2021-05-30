set(CMAKE_CXX_STANDARD 14)

# xray-event
# xray-chan (for tracee & tracer by ifdef flag)
add_subdirectory(core) # Event (Domain & Index & Handle) + source(for tracee) & sink(for tracer)

# Extensible Domain
# pulsar-ftrace <- SHARED (for tracee & tracer) and INLINE helpers for tracer
add_subdirectory(domain)

# This corresponds to application
add_library(xray-tracee SHARED tracee.cpp)
target_link_libraries(xray-tracee PRIVATE xray-mydomain)

# xray-mux STATIC (Support EventBus and EventListener)
# This is a resuable sink which depends on AWESOME-domain 1/2/3/...
add_subdirectory(endpoint)

add_executable(xray-tracer tracer.cpp)
target_link_libraries(xray-tracer PRIVATE xray-mydomain)
target_link_libraries(xray-tracer PUBLIC xray-endpoint)
target_link_libraries(xray-tracer PRIVATE dl)
