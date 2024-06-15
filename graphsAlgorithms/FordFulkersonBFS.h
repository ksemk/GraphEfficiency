
/**
 * @file FordFulkersonBFS.h
 * @brief This file contains the declaration of the FordFulkersonBFS class.
 */
#ifndef FORDFULKERSONBFS_H
#define FORDFULKERSONBFS_H
#include "../GraphsGenerating.h"

/**
 * @class FordFulkersonBFS
 * @brief Class implementing the Ford-Fulkerson algorithm with BFS for finding the maximum flow in a graph.
 */
class FordFulkersonBFS {
public:
    /**
    * @brief Performs a breadth-first search on a graph represented as an incidence matrix.
    * @param incMatrix The incidence matrix representing the graph.
    * @param source The source vertex.
    * @param sink The sink vertex.
    * @param parent The parent array.
    * @param numVertices The number of vertices in the graph.
    * @param numEdges The number of edges in the graph.
    * @return True if there is a path from source to sink, false otherwise.
    */
    static bool bfsIncMatrix(int **incMatrix, int source, int sink, int parent[], int numVertices, int numEdges);

    /**
     * @brief Executes the Ford-Fulkerson algorithm with BFS on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @return The maximum flow from source to sink.
     */
    static int AlgorithmCalculationFromIncMatrix(int **incMatrix, int source, int sink, int numVertices, int numEdges);

    /**
     * @brief Prints the results of the Ford-Fulkerson algorithm with BFS.
     * @param maxFlow The maximum flow from source to sink.
     * @param elapsed The time taken to execute the algorithm.
     * @param residualGraph The residual graph.
     * @param numVertices The number of vertices in the graph.
     */
    static void PrintResults(int maxFlow, double elapsed, int **residualGraph, int numVertices);

    /**
     * @brief Measures and prints the time taken by the Ford-Fulkerson algorithm with BFS on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     */
    static void TimeCounterIncMatrix(int **incMatrix, int source, int sink, int numVertices, int numEdges);

    /**
     * @brief Performs a breadth-first search on a graph represented as an adjacency list.
     * @param residualGraph The residual graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param parent The parent array.
     * @param numVertices The number of vertices in the graph.
     * @return True if there is a path from source to sink, false otherwise.
     */
    static bool bfsList(slistEl **residualGraph, int source, int sink, int parent[], int numVertices);

    /**
     * @brief Executes the Ford-Fulkerson algorithm with BFS on a graph represented as an adjacency list.
     * @param graph The adjacency list representing the graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param numVertices The number of vertices in the graph.
     * @return The maximum flow from source to sink.
     */
    static int AlgorithmCalculationFromList(slistEl **graph, int source, int sink, int numVertices);

    /**
     * @brief Prints the results of the Ford-Fulkerson algorithm with BFS on a graph represented as an adjacency list.
     * @param maxFlow The maximum flow from source to sink.
     * @param residualGraph The residual graph.
     * @param numVertices The number of vertices in the graph.
     */
    static void PrintResultsList(int maxFlow, slistEl **residualGraph, int numVertices);

    /**
     * @brief Measures and prints the time taken by the Ford-Fulkerson algorithm with BFS on a graph represented as an adjacency list.
     * @param graph The adjacency list representing the graph.
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param numVertices The number of vertices in the graph.
     */
    static void TimeCounterList(slistEl **graph, int source, int sink, int numVertices);
};

#endif