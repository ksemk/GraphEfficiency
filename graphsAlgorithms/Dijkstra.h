```cpp
/**
 * @file Dijkstra.h
 * @brief This file contains the declaration of the Dijkstra and PriorityQueue classes.
 */

#ifndef GRAPHEFFICIENCY_DIJKSTRA_H
#define GRAPHEFFICIENCY_DIJKSTRA_H

#include <utility>
#include "../GraphsGenerating.h"

using namespace std;

/**
 * @class Dijkstra
 * @brief A class for implementing Dijkstra's algorithm.
 *
 * This class provides static methods for running Dijkstra's algorithm on a graph represented as either an adjacency matrix or an adjacency list, printing the results, and measuring the time taken by the algorithm.
 */
class Dijkstra {

public:
    /**
     * @brief Runs Dijkstra's algorithm on a graph represented as an adjacency matrix.
     *
     * @param adjMatrix The adjacency matrix representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     * @return A pair of arrays representing the shortest distances and the previous vertices.
     */
    static pair<int*, int*> AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int startVertex);

    /**
     * @brief Runs Dijkstra's algorithm on a graph represented as an adjacency list.
     *
     * @param adjList The adjacency list representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     * @return A pair of arrays representing the shortest distances and the previous vertices.
     */
    static pair<int*, int*> AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int startVertex);

    /**
     * @brief Prints the results of Dijkstra's algorithm.
     *
     * @param dist The array of shortest distances.
     * @param prev The array of previous vertices.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void PrintResults(int *dist, int *prev, int numVertices, int startVertex);

    /**
     * @brief Measures and prints the time taken by Dijkstra's algorithm on a graph represented as an adjacency matrix.
     *
     * @param adjMatrix The adjacency matrix representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void TimeCounterMatrix(int **adjMatrix, int numVertices, int startVertex);

    /**
     * @brief Measures and prints the time taken by Dijkstra's algorithm on a graph represented as an adjacency list.
     *
     * @param adjList The adjacency list representation of the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void TimeCounterList(slistEl **adjList, int numVertices, int startVertex);
};

/**
 * @class PriorityQueue
 * @brief A class for implementing a priority queue.
 *
 * This class provides methods for creating a priority queue, pushing elements into it, popping elements from it, and checking if it is empty.
 */
class PriorityQueue {
private:
    int* heap; ///< The heap array.
    int* pos; ///< The position array.
    int* dist; ///< The distance array.
    int size; ///< The current size of the priority queue.
    int capacity; ///< The maximum capacity of the priority queue.

    /**
     * @brief Heapifies the priority queue at a given index.
     *
     * @param idx The index to heapify at.
     */
    void heapify(int idx);

    /**
     * @brief Swaps two elements in the priority queue.
     *
     * @param a The first element.
     * @param b The second element.
     */
    void swap(int* a, int* b);

public:
    /**
     * @brief Constructs a new PriorityQueue object.
     *
     * @param capacity The maximum capacity of the priority queue.
     * @param dist The distance array.
     */
    PriorityQueue(int capacity, int* dist);

    /**
     * @brief Destroys the PriorityQueue object.
     */
    ~PriorityQueue();

    /**
     * @brief Pushes an element into the priority queue.
     *
     * @param v The element to push.
     */
    void push(int v);

    /**
     * @brief Pops an element from the priority queue.
     *
     * @return The popped element.
     */
    int pop();

    /**
     * @brief Checks if the priority queue is empty.
     *
     * @return True if the priority queue is empty, false otherwise.
     */
    bool isEmpty();
};

#endif //GRAPHEFFICIENCY_DIJKSTRA_H