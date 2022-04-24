add_library(xray-endpoint SHARED endpoint.cpp)
target_include_directories(xray-endpoint PUBLIC include)
target_link_libraries(xray-endpoint PRIVATE xray-core)
target_link_libraries(xray-endpoint PRIVATE xray-mydomain)
