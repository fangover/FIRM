cmake_minimum_required(VERSION 3.16)
project(ExternLibTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/../../dependency/googletest googletest-build)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

function(add_gtest name file)
    file(GLOB EXTERNLIB_SOURCES "${CMAKE_CURRENT_LIST_DIR}/../source/*.cpp")

    add_executable(${name} ${file} ${EXTERNLIB_SOURCES})
    target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)
    target_link_libraries(${name} gtest_main)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

# Add your test
add_gtest(TestEString testestring.cpp)