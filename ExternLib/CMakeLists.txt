file(GLOB_RECURSE EXTERNLIB_HEADERS include/*.h)
file(GLOB_RECURSE EXTERNLIB_SOURCES source/*.cpp)

add_library(ExternLib STATIC ${EXTERNLIB_SOURCES} ${EXTERNLIB_HEADERS})
target_include_directories(ExternLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(ExternLib PUBLIC cxx_std_20)
set_target_properties(ExternLib PROPERTIES FOLDER "ExternLib")

if(BUILD_TESTING)
    message("test")
    add_subdirectory(test)
endif()