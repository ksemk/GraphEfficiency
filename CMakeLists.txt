cmake_minimum_required(VERSION 3.27)
project(GraphEfficiency)

set(CMAKE_CXX_STANDARD 17)

add_executable(GraphEfficiency main.cpp
        SimulationOptions.cpp
        SimulationOptions.h
        GraphsAlgos.cpp
        GraphsAlgos.h
)
