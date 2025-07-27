add_library(ExampleStrat2 STATIC
    source/detector.cpp
)

target_include_directories(ExampleStrat2
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/core/include
)

target_link_libraries(ExampleStrat2
    PUBLIC StrategyInterface
           ExternLib
)

target_precompile_headers(ExampleStrat2
    PRIVATE ${CMAKE_SOURCE_DIR}/cmake/pch/pch.h
)

set_target_properties(ExampleStrat2 PROPERTIES FOLDER "Core/Strategies")
