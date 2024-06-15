/**
 * @file Dijkstra.h
 * @brief This file contains the declaration of the Dijkstra and PriorityQueue classes.
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <utility>
#include "../GraphsGenerating.h" // Ensure this path is correct and accessible

/**
 * @class PriorityQueue
 * @brief Class implementing a priority queue for use in Dijkstra's algorithm.
 */
class PriorityQueue {
public:
    /**
     * @brief Constructor for the PriorityQueue class.
     * @param capacity The maximum capacity of the priority queue.
     * @param dist The array of distances from the source vertex.
     */
    PriorityQueue(int capacity, int* dist);

    /**
     * @brief Destructor for the PriorityQueue class.
     */
    ~PriorityQueue();

    /**
     * @brief Inserts a vertex into the priority queue.
     * @param v The vertex to be inserted.
     */
    void push(int v);

    /**
     * @brief Removes and returns the vertex with the highest priority (lowest distance).
     * @return The vertex with the highest priority.
     */
    int pop();

    /**
     * @brief Checks if the priority queue is empty.
     * @return True if the priority queue is empty, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Decreases the key (distance) of a vertex.
     * @param v The vertex whose key is to be decreased.
     */
    void decreaseKey(int v);

private:
    void heapify(int idx);
    void swap(int* a, int* b);
    int* heap;
    int* pos;
    int size;
    int capacity;
    int* dist;
};

/**
 * @class Dijkstra
 * @brief Class implementing Dijkstra's algorithm for finding the shortest paths in a graph.
 */
class Dijkstra {
public:
    /**
     * @brief Executes Dijkstra's algorithm on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @param startVertex The starting vertex for the algorithm.
     * @return A pair of arrays representing the shortest distances and the previous vertices.
     */
    static std::pair<int*, int*> AlgorithmCalculationFromMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex);

    /**
     * @brief Executes Dijkstra's algorithm on a graph represented as an adjacency list.
     * @param adjList The adjacency list representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     * @return A pair of arrays representing the shortest distances and the previous vertices.
     */
    static std::pair<int*, int*> AlgorithmCalculationFromList(slistEl** adjList, int numVertices, int startVertex);

    /**
     * @brief Prints the results of Dijkstra's algorithm.
     * @param dist The array of shortest distances.
     * @param prev The array of previous vertices.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void PrintResults(int* dist, int* prev, int numVertices, int startVertex);

    /**
     * @brief Measures and prints the time taken by Dijkstra's algorithm on a graph represented as an adjacency list.
     * @param adjList The adjacency list representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void TimeCounterList(slistEl** adjList, int numVertices, int startVertex);

    /**
     * @brief Measures and prints the time taken by Dijkstra's algorithm on a graph represented as an incidence matrix.
     * @param incMatrix The incidence matrix representing the graph.
     * @param numVertices The number of vertices in the graph.
     * @param numEdges The number of edges in the graph.
     * @param startVertex The starting vertex for the algorithm.
     */
    static void TimeCounterMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex);
};

#endif // DIJKSTRA_H