# clang-toolchain.cmake
set(CMAKE_SYSTEM_NAME Windows)

# Point to Clang executables
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")

set(CMAKE_MAKE_PROGRAM "C:/Program Files/Ninja/ninja.exe") # Adjust if needed

set(CMAKE_C_FLAGS "--target=x86_64-w64-windows-gnu")
set(CMAKE_CXX_FLAGS "--target=x86_64-w64-windows-gnu")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)