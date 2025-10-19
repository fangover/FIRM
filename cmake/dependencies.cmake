find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

set(IMGUI_DIR "/opt/imgui" CACHE PATH "Dear ImGui root")

add_library(imgui STATIC
  "${IMGUI_DIR}/imgui.cpp"
  "${IMGUI_DIR}/imgui_draw.cpp"
  "${IMGUI_DIR}/imgui_tables.cpp"
  "${IMGUI_DIR}/imgui_widgets.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui PUBLIC
  "${IMGUI_DIR}"
  "${IMGUI_DIR}/backends"
  "${IMGUI_DIR}/examples/libs/gl3w"
)

target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GL3W)

if(TARGET OpenGL::GL)
  set(_OPENGL_TARGET OpenGL::GL)
else()
  set(_OPENGL_TARGET OpenGL::OpenGL)
endif()

target_link_libraries(imgui PUBLIC glfw ${_OPENGL_TARGET})

find_package(GTest REQUIRED)
find_package(CURL REQUIRED)
