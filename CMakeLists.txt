cmake_minimum_required(VERSION 3.27)
project(GraphEfficiency)

set(CMAKE_CXX_STANDARD 17)

add_executable(GraphEfficiency main.cpp
        SimulationOptions.cpp
        SimulationOptions.h
        GraphsGenerating.cpp
        GraphsGenerating.h
        graphsAlgorithms/Prim.cpp
        graphsAlgorithms/Prim.h
        graphsAlgorithms/Kruskal.cpp
        graphsAlgorithms/Kruskal.h
        graphsAlgorithms/Dijkstra.cpp
        graphsAlgorithms/Dijkstra.h
        graphsAlgorithms/BellmanFord.cpp
        graphsAlgorithms/BellmanFord.h
        graphsAlgorithms/FordFulkersonDFS.cpp
        graphsAlgorithms/FordFulkersonDFS.h
        graphsAlgorithms/FordFulkersonBFS.cpp
        graphsAlgorithms/FordFulkersonBFS.h
)
