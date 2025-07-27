add_library(Core INTERFACE)

target_include_directories(Core
    INTERFACE ${CMAKE_SOURCE_DIR}
              ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(strategies)

set_target_properties(Core PROPERTIES FOLDER "Core")
