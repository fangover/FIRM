add_executable(main
    source/launcher.cpp
    source/main.cpp
)

target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(main PRIVATE 
    Engine
    Renderer
)

target_precompile_headers(main PRIVATE ${CMAKE_SOURCE_DIR}/cmake/pch/pch.h)

set_target_properties(main PROPERTIES FOLDER "App" RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
