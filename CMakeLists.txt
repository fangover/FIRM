cmake_minimum_required(VERSION 3.20)
project(TradeManager LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -Wunused-parameter
    -fexec-charset=UTF-8
    -fdiagnostics-color=always
)

# Output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/pch/pch.cmake)

# ImGui
add_library(imgui STATIC
    dependency/imgui/imgui.cpp
    dependency/imgui/imgui_draw.cpp
    dependency/imgui/imgui_tables.cpp
    dependency/imgui/imgui_widgets.cpp
    dependency/imgui/backends/imgui_impl_glfw.cpp
    dependency/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    dependency/imgui
    dependency/imgui/backends
)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -w")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -w")
add_subdirectory(dependency/glfw)

find_package(OpenGL REQUIRED)

# Global include
include_directories(    
    # dependency/imgui
    # dependency/imgui/backends
    dependency/glfw/include
    ExternLib/include
)

# Add subdirectories
add_subdirectory(ExternLib)
add_subdirectory(Core)
add_subdirectory(App)