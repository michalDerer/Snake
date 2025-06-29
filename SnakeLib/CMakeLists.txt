# CMakeList.txt : CMake project for SnakeLib, include source and define
# project specific logic here.
#

add_library(SnakeLib STATIC "source/SnakeLib.cpp" "include/SnakeLib.hpp")
#include_directories("include")
target_include_directories(SnakeLib PUBLIC "include")
#target_include_directories(SnakeLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SnakeLib PROPERTY CXX_STANDARD 20)
endif()
