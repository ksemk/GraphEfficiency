/**
 * @file FordFulkersonDFS.h
 * @brief This file contains the declaration of the FordFulkersonDFS class.
 */

#ifndef FORDFULKERSONDFS_H
#define FORDFULKERSONDFS_H

#include "../GraphsGenerating.h"

/**
 * @class FordFulkersonDFS
 * @brief A class for implementing Ford-Fulkerson algorithm using Depth-First Search (DFS).
 *
 * This class provides static methods for running the Ford-Fulkerson algorithm on a graph represented as either an adjacency matrix or an adjacency list, printing the results, and measuring the time taken by the algorithm.
 */
class FordFulkersonDFS {
public:
    /**
     * @brief Performs a DFS on the residual graph and returns true if there is a path from source to sink.
     *
     * @param residualGraph The residual graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param parent The parent array.
     * @param numVertices The number of vertices in the graph.
     * @return True if there is a path from source to sink, false otherwise.
     */
    static bool dfs(int **residualGraph, int source, int sink, int parent[], int numVertices);

    /**
     * @brief Performs a DFS on the residual graph (represented as an adjacency list) and returns true if there is a path from source to sink.
     *
     * @param residualGraph The residual graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param parent The parent array.
     * @param numVertices The number of vertices in the graph.
     * @return True if there is a path from source to sink, false otherwise.
     */
    static bool dfsList(slistEl **residualGraph, int source, int sink, int parent[], int numVertices);

    /**
     * @brief Runs the Ford-Fulkerson algorithm on a graph represented as an adjacency matrix.
     *
     * @param graph The graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param numVertices The number of vertices in the graph.
     * @return The maximum flow.
     */
    static int AlgorithmCalculationFromMatrix(int **graph, int source, int sink, int numVertices);

    /**
     * @brief Runs the Ford-Fulkerson algorithm on a graph represented as an adjacency list.
     *
     * @param graph The graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param numVertices The number of vertices in the graph.
     * @return The maximum flow.
     */
    static int AlgorithmCalculationFromList(slistEl **graph, int source, int sink, int numVertices);

    /**
     * @brief Prints the results of the Ford-Fulkerson algorithm.
     *
     * @param maxFlow The maximum flow.
     * @param elapsed The time taken by the algorithm, in seconds.
     * @param residualGraph The residual graph.
     * @param numVertices The number of vertices in the graph.
     */
    static void PrintResults(int maxFlow, double elapsed, int **residualGraph, int numVertices);

    /**
     * @brief Prints the results of the Ford-Fulkerson algorithm for a graph represented as an adjacency list.
     *
     * @param maxFlow The maximum flow.
     * @param elapsed The time taken by the algorithm, in seconds.
     * @param residualGraph The residual graph.
     * @param numVertices The number of vertices in the graph.
     */
    static void PrintResultsList(int maxFlow, double elapsed, slistEl **residualGraph, int numVertices);

    /**
     * @brief Measures and prints the time taken by the Ford-Fulkerson algorithm on a graph represented as an adjacency matrix.
     *
     * @param graph The graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param numVertices The number of vertices in the graph.
     */
    static void TimeCounterMatrix(int **graph, int source, int sink, int numVertices);

    /**
     * @brief Measures and prints the time taken by the Ford-Fulkerson algorithm on a graph represented as an adjacency list.
     *
     * @param graph The graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param numVertices The number of vertices in the graph.
     */
    static void TimeCounterList(slistEl **graph, int source, int sink, int numVertices);
};

#endif // FORDFULKERSONDFS_H