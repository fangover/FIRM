cmake_minimum_required(VERSION 3.20)
project(FIRM LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Apply warning flags only to C++ sources to avoid breaking C libraries
add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Werror>
    $<$<COMPILE_LANGUAGE:CXX>:-Wpedantic>
    $<$<COMPILE_LANGUAGE:CXX>:-Wunused-parameter>
    $<$<COMPILE_LANGUAGE:CXX>:-fexec-charset=UTF-8>
    $<$<COMPILE_LANGUAGE:CXX>:-fdiagnostics-color=always>
)

# Output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/pch/pch.cmake)

enable_testing()
find_package(OpenGL REQUIRED)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)

# Global include
include_directories(    
    ExternLib/include
)

# Add subdirectories
add_subdirectory(externlib)
add_subdirectory(core)
add_subdirectory(app)