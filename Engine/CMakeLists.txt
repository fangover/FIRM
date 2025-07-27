add_library(Engine STATIC
    source/engine.cpp
)

target_include_directories(Engine
    PUBLIC 
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Engine
    PUBLIC Core
           ExternLib
           ExampleStrat1
)

target_precompile_headers(Engine
    PRIVATE ${CMAKE_SOURCE_DIR}/cmake/pch/pch.h
)

set_target_properties(Engine PROPERTIES FOLDER "Engine")
