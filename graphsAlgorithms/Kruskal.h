/**
    * @brief Finds the vertex with the minimum key value, from the set of vertices not yet included in the MST.
    * @param key Array of key values.
    * @param inMST Array indicating whether a vertex is included in the MST.
    * @param numVertices Number of vertices in the graph.
    * @return Index of the vertex with the minimum key value.
    */
#ifndef KRUSKAL_H
#define KRUSKAL_H


#include "../GraphsGenerating.h"

/**
 * @class Kruskal
 * @brief Class implementing Kruskal's algorithm for finding the minimum spanning tree in a graph.
 */
class Kruskal {
public:
    /**
     * @struct Edge
     * @brief Struct representing an edge in a graph.
     */
    struct Edge {
        int src; ///< The source vertex of the edge
        int dest; ///< The destination vertex of the edge
        int weight; ///< The weight of the edge
    };

    static Edge* mst;
    static int mstSize;

    static int find(int parent[], int i);
    static void Union(int parent[], int rank[], int x, int y);

/**
     * @brief Executes Kruskal's algorithm on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @return The total weight of the minimum spanning tree.
     */
    static int AlgorithmCalculationFromMatrix(int **incMatrix, int numVertices, int numEdges);

    /**
     * @brief Executes Kruskal's algorithm on a graph represented as an adjacency list.
     * @param adjList The adjacency list representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @return The total weight of the minimum spanning tree.
     */
    static int AlgorithmCalculationFromList(slistEl **adjList, int numVertices);

    /**
     * @brief Prints the results of Kruskal's algorithm.
     * @param mstWeight The total weight of the minimum spanning tree.
     * @param elapsed The time taken to execute the algorithm.
     */
    static void PrintResults(int mstWeight, double elapsed);

    /**
     * @brief Measures and prints the time taken by Kruskal's algorithm on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     */
    static void TimeCounterMatrix(int **incMatrix, int numVertices, int numEdges);

    /**
     * @brief Measures and prints the time taken by Kruskal's algorithm on a graph represented as an adjacency list.
     * @param adjList The adjacency list representing the graph.
     * @param numVertices The number of vertices in the graph.
     */
    static void TimeCounterList(slistEl **adjList, int numVertices);
};

#endif // KRUSKAL_H
