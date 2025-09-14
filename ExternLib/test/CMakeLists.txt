cmake_minimum_required(VERSION 3.16)
project(ExternLibTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest CONFIG REQUIRED)

function(add_gtest TARGET_NAME FILEPATH)
  add_executable(${TARGET_NAME} ${FILEPATH})
  target_link_libraries(${TARGET_NAME} PRIVATE GTest::gtest_main ExternLib)
  add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

# Add your test
add_gtest(TestEString testestring.cpp)