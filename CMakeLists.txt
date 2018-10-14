# Basic CMake file

cmake_minimum_required(VERSION 2.8.0)
project(cpp) # Tell CMake this is a C++ project

IF(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    MESSAGE(FATAL_ERROR "Don't run cmake from the top source directory (you wouldn't want to clutter it, right!!). Create a directory called 'build', then run cmake ..! (if you already tried to make, delete CMakeCache.txt and try again")
ENDIF(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -pedantic -std=c++14")
include_directories(include)

file(GLOB SOURCES "source/*.cpp")

add_executable(mazer ${SOURCES})

