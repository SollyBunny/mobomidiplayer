cmake_minimum_required(VERSION 3.10)
project(mobomidiplayer C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_C_FILES   "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE SRC_CPP_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

message(STATUS "SRC_C_FILES: ${SRC_C_FILES}")
message(STATUS "SRC_CPP_FILES: ${SRC_CPP_FILES}")

add_executable(${PROJECT_NAME} ${SRC_C_FILES} ${SRC_CPP_FILES})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/src/lib)
