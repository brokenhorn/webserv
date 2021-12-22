cmake_minimum_required(VERSION 3.20)
project(testhttp)

set(CMAKE_CXX_STANDARD 98)

add_executable(testhttp start.cpp Server.hpp Server.cpp ServerUnit.cpp ServerUnit.hpp Request.cpp Request.hpp parser.hpp parser.cpp)
