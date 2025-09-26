function(add_module TARGET_NAME SRC_DIR)
    set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}")

    file(GLOB_RECURSE MODULE_SRC CONFIGURE_DEPENDS
        "${MODULE_DIR}/*.cpp"
        "${MODULE_DIR}/*.cxx"
        "${MODULE_DIR}/*.cc"
        "${MODULE_DIR}/*.h"
        "${MODULE_DIR}/*.hpp"
    )

    add_library(${TARGET_NAME} STATIC ${MODULE_SRC})

    target_include_directories(${TARGET_NAME}
        PUBLIC
            "${MODULE_DIR}"
        PRIVATE
            "${PROJECT_SOURCE_DIR}/core"
    )

    target_link_libraries(${TARGET_NAME}
        PRIVATE
            common
            imgui
    )

    target_precompile_headers(${TARGET_NAME}
        PRIVATE "${PROJECT_SOURCE_DIR}/cmake/pch/pch.h"
    )
endfunction()

add_module(CoreModulesGui gui)
add_module(CoreModulesSerialization serialization)
add_module(CoreModulesBot bot)
