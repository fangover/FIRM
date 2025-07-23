add_executable(main
    source/main.cpp
)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR} 
)

target_link_libraries(main PRIVATE ExternalLib)
