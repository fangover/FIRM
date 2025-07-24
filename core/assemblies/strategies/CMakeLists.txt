project(Strategies)

add_subdirectory(scalpingm1)

add_library(Strategies INTERFACE)

target_link_libraries(Strategies INTERFACE
    ScalpingM1
)

target_include_directories(Strategies INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)
