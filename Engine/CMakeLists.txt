file(GLOB_RECURSE engine_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_executable(engine ${engine_SOURCES})

target_include_directories(engine PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/ExternalLib/include
    ${PROJECT_SOURCE_DIR}/engine/include
)

target_link_libraries(engine
    Core
    ExternalLib
)

set_target_properties(engine PROPERTIES
    OUTPUT_NAME "main"
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
)