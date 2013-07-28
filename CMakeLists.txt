cmake_minimum_required(VERSION 2.6)

project(SPELL_CHECK)
 
set(CMAKE_CXX "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic -pedantic-errors -g")

message(${CMAKE_BINARY_DIR})

set(Compiler_SOURCES
  src/patriciaTrie/main.cpp
  src/patriciaTrie/patriciaTrie.cpp
  )

set(Interpreter_SOURCES
  src/interpreter/main.cpp
  src/interpreter/interpreter.cpp
  src/patriciaTrie/patriciaTrie.cpp
  )


find_package(Boost 1.5 COMPONENTS serialization REQUIRED)
if (Boost_FOUND)
  link_directories(${Boost_LIBRARY_DIRS})
  include_directories(${Boost_INCLUDE_DIRS})
 
  add_executable(TextMiningApp ${Interpreter_SOURCES})
  target_link_libraries(TextMiningApp ${Boost_LIBRARIES})

  add_executable(interpreter ${Interpreter_SOURCES})
  target_link_libraries(interpreter ${Boost_LIBRARIES})
endif()

add_custom_target(distclean COMMAND rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake interpreter TextMiningCompiler)
