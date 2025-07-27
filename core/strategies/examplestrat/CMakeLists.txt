add_library(ExampleStrat1 STATIC
    source/detector.cpp
)

target_include_directories(ExampleStrat1
    PUBLIC ${CMAKE_SOURCE_DIR}
)

target_link_libraries(ExampleStrat1
    PUBLIC StrategyInterface
           ExternLib
)

target_precompile_headers(ExampleStrat1
    PRIVATE ${CMAKE_SOURCE_DIR}/cmake/pch/pch.h
)

set_target_properties(ExampleStrat1 PROPERTIES FOLDER "Core/Strategies")
