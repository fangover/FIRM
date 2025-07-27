add_library(Renderer STATIC
    source/Renderer.cpp
)

target_include_directories(Renderer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Renderer PUBLIC 
    ExternLib
)

target_precompile_headers(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/cmake/pch/pch.h)

set_target_properties(Renderer PROPERTIES FOLDER "Modules/Renderer")
