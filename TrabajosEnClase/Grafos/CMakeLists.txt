cmake_minimum_required(VERSION 3.29)
project(grafos)

set(CMAKE_CXX_STANDARD 20)

add_executable(grafos main.cpp
        arista.cpp
        arista.h
        nodo.cpp
        nodo.h)
