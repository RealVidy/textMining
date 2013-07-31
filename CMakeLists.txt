cmake_minimum_required(VERSION 2.6)

project(SPELL_CHECK) 
 
SET (CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -g -Wall -Werror -Wextra -pedantic")
SET (CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -march=native -Wall -Werror -Wextra -pedantic")

set(Prg_compiler_name TextMiningCompiler)
set(Prg_interpreter_name TextMiningApp)

set(Compiler_SOURCES
  src/compilator/main.cpp
  src/compilator/compilator.cpp
  )

set(Interpreter_SOURCES
  src/interpreter/main.cpp
  src/interpreter/interpreter.cpp
  src/compilator/compilator.cpp
  )

add_executable(${Prg_compiler_name} ${Compiler_SOURCES})
add_executable(${Prg_interpreter_name} ${Interpreter_SOURCES})

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

find_package(Doxygen)
if (DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

add_custom_target(distclean COMMAND rm -rf ${Prg_compiler_name} ${Prg_interpreter_name} cmake_install.cmake CMakeCache.txt CMakeFiles)