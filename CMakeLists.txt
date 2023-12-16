project(IM)

cmake_minimum_required(VERSION 3.24)

# file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/utils
    ${PROJECT_SOURCE_DIR}/src/model
    ${PROJECT_SOURCE_DIR}/src/method
)

set(CMAKE_CXX_FLAGS "-O2 -Wall -std=c++2a")

add_executable(runner ${PROJECT_SOURCE_DIR}/src/runner/runner.cpp)
