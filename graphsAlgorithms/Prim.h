/**
 * @file Prim.h
 * @brief This file contains the declaration of the Prim class.
 */

#ifndef PRIM_H
#define PRIM_H

#include "../GraphsGenerating.h" // Ensure this path is correct and accessible

/**
 * @class Prim
 * @brief Class implementing Prim's algorithm for finding the minimum spanning tree in a graph.
 */
class Prim {
public:
    /**
     * @struct Edge
     * @brief Struct representing an edge in a graph.
     */
    struct Edge {
        int src; // The source vertex of the edge
        int dest; // The destination vertex of the edge
        int weight; // The weight of the edge
    };


    /**
     * @brief Executes Prim's algorithm on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @return The total weight of the minimum spanning tree.
     */
    static int AlgorithmCalculationFromMatrix(int **incMatrix, int numVertices, int numEdges);

    /**
     * @brief Executes Prim's algorithm on a graph represented as an adjacency list.
     * @param adjList The adjacency list representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @return The total weight of the minimum spanning tree.
     */
    static int AlgorithmCalculationFromList(slistEl **adjList, int numVertices);

    /**
     * @brief Prints the results of Prim's algorithm.
     * @param mstWeight The total weight of the minimum spanning tree.
     * @param elapsed The time taken to execute the algorithm.
     */
    static void PrintResults(int mstWeight, double elapsed);
    /**
    * @brief Measures and prints the time taken by Prim's algorithm on a graph represented as an incidence matrix.
    * @param incMatrix The incidence matrix representing the graph.
    * @param numVertices The number of vertices in the graph.
    * @param numEdges The number of edges in the graph.
    */
    static void TimeCounterMatrix(int **incMatrix, int numVertices, int numEdges);

    /**
     * @brief Measures and prints the time taken by Prim's algorithm on a graph represented as an adjacency list.
     * @param adjList The adjacency list representing the graph.
     * @param numVertices The number of vertices in the graph.
     */
    static void TimeCounterList(slistEl **adjList, int numVertices);

    /**
    * @brief Finds the vertex with the minimum key value, from the set of vertices not yet included in the MST.
    * @param key Array of key values.
    * @param inMST Array indicating whether a vertex is included in the MST.
    * @param numVertices Number of vertices in the graph.
    * @return Index of the vertex with the minimum key value.
    */
    static int minKey(int* key, bool* inMST, int numVertices); // Ensure this is declared as static and matches the definition

private:
    static Edge* mst; // The resulting MST, stored as an array of edges
    static int mstSize; // Size of the MST array
};

#endif
