cmake_minimum_required(VERSION 3.16)
project(ExternLibTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

function(add_gtest name file)
    add_executable(${name} ${file})
    target_link_libraries(${name} gtest_main ExternLib)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

# Add your test
add_gtest(TestEString testestring.cpp)