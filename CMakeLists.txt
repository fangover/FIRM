cmake_minimum_required(VERSION 3.20)
project(TradeManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

# Compiler flags
add_compile_options(
    -Wall -Wextra -Werror -Wpedantic
    -Wunused-parameter
    -fexec-charset=UTF-8
    -fdiagnostics-color=always
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Global include
# include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(externallib)
add_subdirectory(core)
add_subdirectory(engine)
add_subdirectory(modules)
add_subdirectory(app)