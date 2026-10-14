cmake_minimum_required(VERSION 3.12)

project(Yac LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES "src/*.cpp")

add_executable(yac ${SOURCES})

target_include_directories(yac PRIVATE include)

target_compile_options(yac PRIVATE
    -Wall
    -Wextra
    -O2
)
