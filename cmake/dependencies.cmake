cmake_minimum_required(VERSION 3.20)
project(MyApp CXX)

include(FetchContent)
find_package(OpenGL REQUIRED)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/dependency")
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(TARGET_GLFW_DIR  "${CMAKE_SOURCE_DIR}/dependency/glfw"  CACHE PATH "Existing GLFW source dir")
set(TARGET_IMGUI_DIR "${CMAKE_SOURCE_DIR}/dependency/imgui" CACHE PATH "Existing ImGui source dir")

set(GLFW_TAG  "3.3.8"   CACHE STRING "GLFW git tag")
set(IMGUI_TAG "v1.90.4" CACHE STRING "ImGui git tag")

# ========================= GLFW ==============================================
if(NOT TARGET glfw)

  if(EXISTS "${TARGET_GLFW_DIR}/CMakeLists.txt")
    message(STATUS "Using target GLFW at ${TARGET_GLFW_DIR}")
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory("${TARGET_GLFW_DIR}" "${CMAKE_BINARY_DIR}/glfw-build")
  else()
    FetchContent_Declare(
      glfw
      GIT_REPOSITORY https://github.com/glfw/glfw.git
      GIT_TAG        ${GLFW_TAG}
    )
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(glfw)
  endif()
endif()

# ========================= ImGui =============================================
if(NOT TARGET imgui)
  if(EXISTS "${TARGET_IMGUI_DIR}/imgui.cpp")
    message(STATUS "Using target ImGui at ${TARGET_IMGUI_DIR}")
    add_library(imgui STATIC
      ${TARGET_IMGUI_DIR}/imgui.cpp
      ${TARGET_IMGUI_DIR}/imgui_draw.cpp
      ${TARGET_IMGUI_DIR}/imgui_tables.cpp
      ${TARGET_IMGUI_DIR}/imgui_widgets.cpp
      ${TARGET_IMGUI_DIR}/backends/imgui_impl_glfw.cpp
      ${TARGET_IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    )
    target_include_directories(imgui PUBLIC
      ${TARGET_IMGUI_DIR}
      ${TARGET_IMGUI_DIR}/backends
    )
    target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
  else()
    FetchContent_Declare(
      imgui
      GIT_REPOSITORY https://github.com/ocornut/imgui.git
      GIT_TAG        ${IMGUI_TAG}
    )
    FetchContent_GetProperties(imgui)
    if(NOT imgui_POPULATED)
      FetchContent_Populate(imgui)
      add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
      )
      target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
      )
      target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
    endif()
  endif()
endif()