file(GLOB_RECURSE ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_executable(Engine ${ENGINE_SOURCES})

target_include_directories(Engine PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/ExternalLib/include
    ${PROJECT_SOURCE_DIR}/Engine/include
)

target_link_libraries(Engine
    Core
    ExternalLib
)

set_target_properties(Engine PROPERTIES
    OUTPUT_NAME "main"
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
)