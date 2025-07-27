add_library(CoreStrategiesExample STATIC
    source/detector.cpp
)

target_include_directories(CoreStrategiesExample PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(CoreStrategiesExample PUBLIC 
    CoreStrategies
    ExternLib
)

target_precompile_headers(CoreStrategiesExample PRIVATE ${CMAKE_SOURCE_DIR}/cmake/pch/pch.h)

set_target_properties(CoreStrategiesExample PROPERTIES FOLDER "Core/Strategies")
