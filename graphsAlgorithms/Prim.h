/**
 * @file Prim.h
 * @brief This file contains the declaration of the Prim class.
 */

#ifndef PRIM_H
#define PRIM_H

#include <vector>
#include "../GraphsGenerating.h"

/**
 * @class Prim
 * @brief A class for implementing Prim's algorithm.
 *
 * This class provides static methods for running Prim's algorithm on a graph represented as either an adjacency matrix or an adjacency list, printing the results, and measuring the time taken by the algorithm.
 * The resulting Minimum Spanning Tree (MST) is stored as a vector of edges.
 */
class Prim {
public:
    /**
     * @brief Runs Prim's algorithm on a graph represented as an adjacency matrix.
     *
     * @param adjMatrix The adjacency matrix representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @return The total weight of the MST.
     */
    static int AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices);

    /**
     * @brief Runs Prim's algorithm on a graph represented as an adjacency list.
     *
     * @param adjList The adjacency list representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @return The total weight of the MST.
     */
    static int AlgorithmCalculationFromList(slistEl **adjList, int numVertices);

    /**
     * @brief Prints the results of Prim's algorithm.
     *
     * @param mstWeight The total weight of the MST.
     * @param elapsed The time taken by the algorithm, in seconds.
     */
    static void PrintResults(int mstWeight, double elapsed);

    /**
     * @brief Measures and prints the time taken by Prim's algorithm on a graph represented as an adjacency matrix.
     *
     * @param adjMatrix The adjacency matrix representation of the graph.
     * @param numVertices The number of vertices in the graph.
     */
    static void TimeCounterMatrix(int **adjMatrix, int numVertices);

    /**
     * @brief Measures and prints the time taken by Prim's algorithm on a graph represented as an adjacency list.
     *
     * @param adjList The adjacency list representation of the graph.
     * @param numVertices The number of vertices in the graph.
     */
    static void TimeCounterList(slistEl **adjList, int numVertices);

private:
    /**
     * @struct Edge
     * @brief A struct representing an edge in a graph.
     *
     * This struct represents an edge in a graph, which consists of a source vertex, a destination vertex, and a weight.
     */
    struct Edge {
        int src; ///< The source vertex of the edge
        int dest; ///< The destination vertex of the edge
        int weight; ///< The weight of the edge
    };

    /**
     * @brief Finds the vertex with the minimum key value, from the set of vertices not yet included in the MST.
     *
     * @param key The key values of the vertices.
     * @param inMST A boolean vector indicating whether each vertex is included in the MST.
     * @param numVertices The number of vertices in the graph.
     * @return The index of the vertex with the minimum key value.
     */
    static int minKey(const std::vector<int>& key, const std::vector<bool>& inMST, int numVertices);

    static std::vector<Edge> mst; ///< The resulting MST, stored as a vector of edges
};

#endif