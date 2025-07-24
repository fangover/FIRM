project(ExternalLib)

file(GLOB_RECURSE EXTERN_SRC CONFIGURE_DEPENDS source/*.cpp)
file(GLOB_RECURSE EXTERN_INC CONFIGURE_DEPENDS include/*.h)

add_library(ExternalLib STATIC ${EXTERN_SRC})
target_include_directories(ExternalLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)