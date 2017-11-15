cmake_minimum_required(VERSION 2.6)
project(Graphs)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Graphs src/main.cpp)

install(TARGETS Graphs RUNTIME DESTINATION bin)
