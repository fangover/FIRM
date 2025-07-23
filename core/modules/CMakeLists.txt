function(add_module TARGET_NAME SRC_DIR)
    file(GLOB_RECURSE MODULE_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/*.h"
    )

    add_library(${TARGET_NAME} STATIC ${MODULE_SRC})
    target_include_directories(${TARGET_NAME} PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}
        ${PROJECT_SOURCE_DIR}/Core
        ${CMAKE_SOURCE_DIR}/dependency/imgui
        ${CMAKE_SOURCE_DIR}/dependency/imgui/backends
    )
    target_link_libraries(${TARGET_NAME} PRIVATE common)

    target_precompile_headers(${TARGET_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/cmake/pch/pch.h")
endfunction()

add_module(CoreModulesGui gui)
