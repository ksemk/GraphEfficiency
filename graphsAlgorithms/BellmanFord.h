#ifndef GRAPHEFFICIENCY_BELLMANFORD_H
#define GRAPHEFFICIENCY_BELLMANFORD_H

#include "../GraphsGenerating.h"
#include <utility>

/**
 * @class BellmanFord
 * @brief This class implements the Bellman-Ford algorithm for finding the shortest path in a graph.
 */
class BellmanFord {
public:
    /**
     * @brief This function implements the Bellman-Ford algorithm using adjacency matrix representation of the graph.
     * @param adjMatrix The adjacency matrix representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     * @return A pair of arrays, where the first array contains the shortest distances from the start vertex to all other vertices,
     * and the second array contains the previous vertex in the shortest path from the start vertex to each vertex.
     */
    static std::pair<int*, int*> AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int startVertex);

    /**
     * @brief This function implements the Bellman-Ford algorithm using adjacency list representation of the graph.
     * @param adjList The adjacency list representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     * @return A pair of arrays, where the first array contains the shortest distances from the start vertex to all other vertices,
     * and the second array contains the previous vertex in the shortest path from the start vertex to each vertex.
     */
    static std::pair<int*, int*> AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int startVertex);

    /**
     * @brief This function prints the results of the Bellman-Ford algorithm.
     * It prints the shortest distance from the start vertex to each vertex, and the shortest path from the start vertex to each vertex.
     * @param dist The array of shortest distances from the start vertex to each vertex.
     * @param prev The array of previous vertices in the shortest path from the start vertex to each vertex.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void PrintResults(int *dist, int *prev, int numVertices, int startVertex);

    /**
     * @brief This function measures the time taken by the Bellman-Ford algorithm using adjacency matrix representation of the graph.
     * It runs the algorithm a specified number of times and prints the average time taken.
     * @param adjMatrix The adjacency matrix representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void TimeCounterMatrix(int **adjMatrix, int numVertices, int startVertex);

    /**
     * @brief This function measures the time taken by the Bellman-Ford algorithm using adjacency list representation of the graph.
     * It runs the algorithm a specified number of times and prints the average time taken.
     * @param adjList The adjacency list representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void TimeCounterList(slistEl **adjList, int numVertices, int startVertex);
};

#endif //GRAPHEFFICIENCY_BELLMANFORD_H