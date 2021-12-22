cmake_minimum_required(VERSION 3.19)
project(HTTP)

set(CMAKE_CXX_STANDARD 98)

add_executable(HTTP main.cpp Request.cpp Request.hpp Response.cpp Response.hpp ../parser/parser.hpp)