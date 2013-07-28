cmake_minimum_required(VERSION 2.6)

project(SPELL_CHECK)
 
set(CMAKE_CXX "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic -pedantic-errors -march=native")

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
 
  add_executable(TextMiningCompiler ${Compiler_SOURCES})
  add_executable(TextMiningApp ${Interpreter_SOURCES})

  target_link_libraries(TextMiningApp ${Boost_LIBRARIES})
  target_link_libraries(TextMiningCompiler ${Boost_LIBRARIES})
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile @ONLY)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
  COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif()

add_custom_target(clean COMMAND rm -rf *~)
add_custom_target(distclean COMMAND rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake TextMiningApp TextMiningCompiler)

