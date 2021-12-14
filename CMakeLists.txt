cmake_minimum_required(VERSION 3.19)
project(parserHTML)

set(CMAKE_CXX_STANDARD 98)

add_executable(parserHTML main.cpp Request.cpp Request.hpp Response.cpp Response.hpp)