file(GLOB_RECURSE ENGINE_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_library(engine STATIC ${ENGINE_SRC})

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/core
)

target_link_libraries(engine
    PRIVATE
        common
        CoreModulesGui
        CoreStrategiesExample
        ExternLib
        imgui
        glfw
        OpenGL::GL
)

target_precompile_headers(engine PRIVATE "${CMAKE_SOURCE_DIR}/cmake/pch/pch.h")
