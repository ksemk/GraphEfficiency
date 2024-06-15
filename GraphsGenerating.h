/**
 * @file GraphsGenerating.h
 * @brief This file contains the declaration of the GraphsGenerating class and the slistEl struct.
 */

#ifndef GRAPHSGENERATING_H
#define GRAPHSGENERATING_H

/**
 * @struct slistEl
 * @brief Struct representing an element in a singly linked list.
 * @var slistEl::v
 * The vertex associated with this list element.
 * @var slistEl::weight
 * The weight of the edge associated with this list element.
 * @var slistEl::next
 * Pointer to the next element in the list.
 */
struct slistEl {
    int v;
    int weight;
    slistEl* next;
};

/**
 * @class GraphsGenerating
 * @brief Class for generating and manipulating graphs.
 * @var GraphsGenerating::incMatrix
 * Incidence matrix of the graph.
 * @var GraphsGenerating::numVertices
 * Number of vertices in the graph.
 * @var GraphsGenerating::numEdges
 * Number of edges in the graph.
 * @var GraphsGenerating::adjList
 * Adjacency list of the graph.
 */
class GraphsGenerating {
public:
    static int** incMatrix; // Incidence matrix
    static int numVertices;
    static int numEdges;
    static slistEl** adjList;

    /**
     * @brief Loads a graph from a file.
     */
    static void loadGraphFromFile();

    /**
     * @brief Prints the incidence matrix of the graph.
     */
    static void printIncidenceMatrix();

    /**
     * @brief Prints the adjacency list of the graph.
     */
    static void printAdjacencyList();

    /**
     * @brief Generates a random graph.
     * @param vertices The number of vertices in the graph.
     * @param density The density of the graph.
     */
    static void generateRandomGraph(int vertices, int density);

    /**
     * @brief Frees the memory allocated for the graph.
     */
    static void freeMemory();
};

#endif // GRAPHSGENERATING_H