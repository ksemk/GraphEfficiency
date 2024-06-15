/**
 * @file BellmanFord.h
 * @brief This file contains the declaration of the BellmanFord class.
 */

#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <utility>
#include "../GraphsGenerating.h" // Ensure this path is correct and accessible

/**
 * @class BellmanFord
 * @brief Class implementing the Bellman-Ford algorithm for finding the shortest paths in a graph.
 */
class BellmanFord {
public:
    /**
     * @brief Executes the Bellman-Ford algorithm on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @param startVertex The starting vertex for the algorithm.
     * @return A pair of arrays representing the shortest distances and the previous vertices.
     */
    static std::pair<int*, int*> AlgorithmCalculationFromMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex);

    /**
     * @brief Executes the Bellman-Ford algorithm on a graph represented as an adjacency list.
     * @param adjList The adjacency list representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     * @return A pair of arrays representing the shortest distances and the previous vertices.
     */
    static std::pair<int*, int*> AlgorithmCalculationFromList(slistEl** adjList, int numVertices, int startVertex);

    /**
     * @brief Prints the results of the Bellman-Ford algorithm.
     * @param dist The array of shortest distances.
     * @param prev The array of previous vertices.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void PrintResults(int* dist, int* prev, int numVertices, int startVertex);

    /**
     * @brief Measures and prints the time taken by the Bellman-Ford algorithm on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void TimeCounterMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex);

    /**
     * @brief Measures and prints the time taken by the Bellman-Ford algorithm on a graph represented as an adjacency list.
     * @param adjList The adjacency list representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void TimeCounterList(slistEl** adjList, int numVertices, int startVertex);
};

#endif // BELLMANFORD_H