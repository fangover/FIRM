add_library(StrategyInterface INTERFACE)

target_include_directories(StrategyInterface
    INTERFACE ${CMAKE_SOURCE_DIR}
              ${CMAKE_CURRENT_SOURCE_DIR}/interface
)

add_subdirectory(example)
add_subdirectory(examplestrat2)

set_target_properties(StrategyInterface PROPERTIES FOLDER "Core/Strategies")
