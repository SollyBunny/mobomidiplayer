cmake_minimum_required(VERSION 3.10)
project(mobomidiplayer C CXX)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SRC_C_FILES   "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} ${SRC_C_FILES})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/src/lib)
