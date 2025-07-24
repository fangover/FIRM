project(Core)

# Add strategies (and any other submodules later)
add_subdirectory(assemblies/strategies)

# Define Core as an INTERFACE target
add_library(Core INTERFACE)

target_include_directories(Core INTERFACE
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/core
)

# Propagate includes and libraries
target_link_libraries(Core INTERFACE
    Strategies
    ExternalLib
)
