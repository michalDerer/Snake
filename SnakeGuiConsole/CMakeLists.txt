# CMakeList.txt : CMake project for SnakeGuiConsole, include source and define
# project specific logic here.
#

add_executable(SnakeGuiConsole "source/SnakeGuiConsole.cpp" "include/SnakeGuiConsole.hpp")
include_directories("include")
target_link_libraries(SnakeGuiConsole PRIVATE SnakeLib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SnakeGuiConsole PROPERTY CXX_STANDARD 20)
endif()