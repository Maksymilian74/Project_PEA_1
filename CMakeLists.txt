cmake_minimum_required(VERSION 3.27)
project(Projekt_PEA_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt_PEA_1 Main/Main.cpp
        Main/Menu.cpp
        Main/Menu.h
        Structures/Matrix.cpp
        Structures/Matrix.h
        Algorithms/Algorithms.cpp
        Algorithms/Algorithms.h
        Utils/ReadFile.cpp
        Utils/ReadFile.h
        Utils/GenerateMatrix.cpp
        Utils/GenerateMatrix.h)

set(CMAKE_EXE_LINKER_FLAGS "-static")
