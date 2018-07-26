cmake_minimum_required(VERSION 3.0.0)
project(mazer)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(build/mazer ${SOURCES})
