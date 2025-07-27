add_library(CoreStrategies INTERFACE)

target_include_directories(CoreStrategies INTERFACE 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)

file(GLOB STRATEGY_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(dir ${STRATEGY_DIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/CMakeLists.txt")
        add_subdirectory(${dir})
    endif()
endforeach()

target_link_libraries(CoreStrategies INTERFACE
    CoreStrategiesExample
)

set_target_properties(CoreStrategies PROPERTIES FOLDER "Core/Strategies")

