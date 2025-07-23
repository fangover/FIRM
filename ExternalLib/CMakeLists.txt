add_library(ExternalLib STATIC
    source/filestreamhandle.cpp
    source/logger.cpp
)

target_include_directories(ExternalLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
