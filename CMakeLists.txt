cmake_minimum_required(VERSION 2.6)

project(SPELL_CHECK)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Werror -pedantic -pedantic-errors -O3 -march=native")
    
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

file(GLOB COMPILE_SRC
  "src/patriciaTrie/*.hpp"
  "src/patriciaTrie/*.cpp"
  "src/*.cpp"
  )

add_executable(compile ${COMPILE_SRC})    

find_package(Boost 1.45.0 COMPONENTS serialization)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS}) 
  target_link_libraries(compile ${Boost_LIBRARIES})      
endif()

