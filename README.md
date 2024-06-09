# Graph Algorithm Efficiency Project

This project is part of a university assignment to study the efficiency of various graph algorithms based on the size of instances and the method of graph representation in computer memory. The project involves implementing and measuring the performance of selected graph algorithms to solve specific problems.

## Project Structure

The project includes the following files:

- `SimulationOptions.cpp`: Contains the options and settings for running the simulations.
- `GraphsGenerating.cpp`: Responsible for generating the graphs used in the simulations.
- `Prim.cpp`: Main file for running Prim's algorithm.
- `Kruskal.cpp`: Main file for running Kruskal's algorithm.
- `Dijkstra.cpp`: Main file for running Dijkstra's algorithm.
- `BellmanFord.cpp`: Main file for running the Bellman-Ford algorithm.
- `FordFulkersonBFS.cpp`: Main file for running the Ford-Fulkerson algorithm for BFS.
- `FordFulkersonDFS.cpp`: Main file for running the Ford-Fulkerson algorithm for DFS.

## Implemented Algorithms

The following algorithms are implemented in this project:

1. **Minimum Spanning Tree (MST) Algorithms:**
   - Prim's Algorithm
   - Kruskal's Algorithm

2. **Shortest Path Algorithms:**
   - Dijkstra's Algorithm
   - Bellman-Ford Algorithm

3. **Maximum Flow Algorithm:**
   - Ford-Fulkerson Algorithm (using both DFS and BFS for path finding)

## Graph Representations

Each algorithm is implemented for two different graph representations:

1. **Matrix Representation** (Adjacency Matrix)
2. **List Representation** (Adjacency List)

## Features

- Dynamic allocation of all data structures.
- Edge weights/capacities are positive integers.
- Time measurements for algorithm performance based on graph size and density.
- Ensures graph connectivity during generation.
- Accurate time measurement using `std::chrono::high_resolution_clock` for Windows in C++.
- Console-based interface for ease of use.

## Usage

The program provides a menu-driven interface to perform the following operations for each graph structure and problem:

1. Load graph data from a file.
2. Generate a random graph.
3. Display the graph in both list and matrix forms.
4. Run the selected algorithm and display results.
