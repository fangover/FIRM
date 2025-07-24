project(Core)

# Add strategies (and any other submodules later)
add_subdirectory(assemblies/strategies)

# Define Core as an INTERFACE target
add_library(Core INTERFACE)

# Propagate includes and libraries
target_link_libraries(Core INTERFACE
    Strategies
    ExternalLib
)
