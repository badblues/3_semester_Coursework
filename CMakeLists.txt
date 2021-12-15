cmake_minimum_required(VERSION 3.18)
project(Coursework)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES src/TLList.h src/TLList.inl)

add_executable(Coursework main.cpp ${SOURCES})
add_definitions(-Wall)

add_subdirectory(googletest)