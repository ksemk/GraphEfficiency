/**
 * @file Kruskal.h
 * @brief This file contains the declaration of the Kruskal class.
 */

#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../GraphsGenerating.h"
#include <vector>

/**
 * @class Kruskal
 * @brief A class for implementing Kruskal's algorithm.
 *
 * This class provides static methods for running Kruskal's algorithm on a graph represented as either an adjacency matrix or an adjacency list, printing the results, and measuring the time taken by the algorithm.
 * The resulting Minimum Spanning Tree (MST) is stored as a vector of edges.
 */
class Kruskal {
public:
    /**
     * @brief Runs Kruskal's algorithm on a graph represented as an adjacency matrix.
     *
     * @param adjMatrix The adjacency matrix representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @return The total weight of the MST.
     */
    static int AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int numEdges);

    /**
     * @brief Runs Kruskal's algorithm on a graph represented as an adjacency list.
     *
     * @param adjList The adjacency list representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @return The total weight of the MST.
     */
    static int AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int numEdges);

    /**
     * @brief Prints the results of Kruskal's algorithm.
     *
     * @param mstWeight The total weight of the MST.
     * @param elapsed The time taken by the algorithm, in seconds.
     */
    static void PrintResults(int mstWeight, double elapsed);

    /**
     * @brief Measures and prints the time taken by Kruskal's algorithm on a graph represented as an adjacency matrix.
     *
     * @param adjMatrix The adjacency matrix representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     */
    static void TimeCounterMatrix(int **adjMatrix, int numVertices, int numEdges);

    /**
     * @brief Measures and prints the time taken by Kruskal's algorithm on a graph represented as an adjacency list.
     *
     * @param adjList The adjacency list representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     */
    static void TimeCounterList(slistEl **adjList, int numVertices, int numEdges);

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
     * @brief Finds the parent of a vertex in the disjoint set.
     *
     * @param parent The parent array.
     * @param i The vertex.
     * @return The parent of the vertex.
     */
    static int find(int parent[], int i);

    /**
     * @brief Unions two sets of vertices.
     *
     * @param parent The parent array.
     * @param rank The rank array.
     * @param x The first set of vertices.
     * @param y The second set of vertices.
     */
    static void Union(int parent[], int rank[], int x, int y);

    /**
     * @brief Sorts the edges of the graph.
     *
     * @param edges The edges of the graph.
     */
    static void sortEdges(std::vector<Edge>& edges);

    static std::vector<Edge> mst; ///< The resulting MST, stored as a vector of edges
};

#endif // KRUSKAL_H