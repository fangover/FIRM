file(GLOB_RECURSE CORE_SOURCES
    assemblies/strategies/**/*.cpp
)

add_library(core STATIC ${CORE_SOURCES})

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/assemblies/strategies/base/interface
    ${CMAKE_CURRENT_SOURCE_DIR}/assemblies/strategies/base/include
    ${CMAKE_CURRENT_SOURCE_DIR}/assemblies/strategies/scalpingm1/include
)
