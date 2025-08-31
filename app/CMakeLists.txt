file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "*.cpp"
    "*.h"
)

add_executable(main ${APP_SOURCES})

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/core
)

target_link_libraries(main PRIVATE 
    engine
    ExternLib
)

target_precompile_headers(main PRIVATE "${CMAKE_SOURCE_DIR}/cmake/pch/pch.h")

set_target_properties(main PROPERTIES
    FOLDER "App"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
