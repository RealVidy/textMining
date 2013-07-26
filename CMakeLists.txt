cmake_minimum_required(VERSION 2.6)

project(SPELL_CHECK)
#SET(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Werror -pedantic -pedantic-errors -O2")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

file(GLOB COMPILE_SRC
    "src/patriciaTrie/*.hpp"
    "src/patriciaTrie/*.cpp"
    "src/*.cpp"
    )

add_executable(compile ${COMPILE_SRC})
