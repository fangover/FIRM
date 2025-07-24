project(ExampleStrat)

file(GLOB_RECURSE ExampleStrat_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_library(ExampleStrat STATIC ${ExampleStrat_SOURCES})

target_include_directories(ExampleStrat
    PRIVATE ${CMAKE_SOURCE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ExampleStrat PUBLIC ExternalLib)
