function(add_strategy TARGET_NAME SRC_DIR)
    file(GLOB_RECURSE STRATEGY_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/*.h"
    )

    add_library(${TARGET_NAME} STATIC ${STRATEGY_SRC})

    target_include_directories(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}
        ${PROJECT_SOURCE_DIR}/core
    )

    target_link_libraries(${TARGET_NAME} PRIVATE strategy_interface)

    target_precompile_headers(${TARGET_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/cmake/pch/pch.h")
endfunction()

add_library(strategy_interface INTERFACE)

target_include_directories(strategy_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/interface)

# Define strategy implementations here
add_strategy(CoreStrategiesExample example)