project(Strategies)

add_subdirectory(ExampleStrat)

add_library(Strategies INTERFACE)

target_link_libraries(Strategies INTERFACE
    ExampleStrat
)

target_include_directories(Strategies INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)
