cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(ShutTheBox)

add_executable(ShutTheBox)
file(GLOB_RECURSE SOURCES "src/*.cpp")
target_sources(ShutTheBox PRIVATE ${SOURCES})