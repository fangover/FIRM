add_library(common INTERFACE)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_precompile_headers(common INTERFACE "${CMAKE_SOURCE_DIR}/cmake/pch/pch.h")