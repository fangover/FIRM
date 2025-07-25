cmake_minimum_required(VERSION 3.20)
project(TradeManagerCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directory setup
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

# Compiler flags
add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -Wunused-parameter
    -fexec-charset=UTF-8
    -fdiagnostics-color=always
)

# Global include paths
include_directories(${PROJECT_SOURCE_DIR}/engine/include)
include_directories(${PROJECT_SOURCE_DIR}/ExternalLib/include)

# Add subdirectories
add_subdirectory(ExternalLib)
add_subdirectory(core)
add_subdirectory(engine)