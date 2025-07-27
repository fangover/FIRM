add_library(CoreStrategies INTERFACE)

target_include_directories(CoreStrategies INTERFACE 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)

add_subdirectory(example)

target_link_libraries(CoreStrategies INTERFACE
    CoreStrategiesExample
)

set_target_properties(CoreStrategies PROPERTIES FOLDER "Core/Strategies")

