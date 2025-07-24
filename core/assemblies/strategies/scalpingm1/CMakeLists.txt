project(ScalpingM1)

file(GLOB_RECURSE SCALPINGM1_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_library(ScalpingM1 STATIC ${SCALPINGM1_SOURCES})

target_include_directories(ScalpingM1
    PRIVATE ${CMAKE_SOURCE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries(ScalpingM1 PUBLIC ExternalLib)
