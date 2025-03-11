cmake_minimum_required(VERSION 3.29)
project(Sources)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sources
        ListaDobleCircular.hpp
        copia.cpp
        ListaDobleCircular.cpp
    main.cpp)
