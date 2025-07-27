add_library(ExternLib STATIC
    source/filestreamhandle.cpp
    source/logger.cpp
)

target_include_directories(ExternLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_precompile_headers(ExternLib
    PRIVATE ${CMAKE_SOURCE_DIR}/cmake/pch/pch.h
)

target_compile_features(ExternLib PUBLIC cxx_std_20)

set_target_properties(ExternLib PROPERTIES FOLDER "External")
