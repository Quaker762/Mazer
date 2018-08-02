# Basic CMake file

cmake_minimum_required(VERSION 3.0.0)
project(cpp) # Tell CMake this is a C++ project

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Weffc++ -pedantic -std=c++14")
include_directories(include)

file(GLOB SOURCES "source/*.cpp")

add_executable(mazer ${SOURCES})
add_executable(mazegen "source/gen/mazegen.cpp")

