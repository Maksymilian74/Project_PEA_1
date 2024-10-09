cmake_minimum_required(VERSION 3.27)
project(Projekt_PEA_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt_PEA_1 Main.cpp
        Menu.cpp
        Menu.h
        Simulation.cpp
        Simulation.h
        Test.cpp
        Test.h)

set(CMAKE_EXE_LINKER_FLAGS "-static")
