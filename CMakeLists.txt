cmake_minimum_required(VERSION 3.21)
project(Project8_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project8_starter_files Input.cpp Parse.h project8.cpp
        project8.h Input.h)
