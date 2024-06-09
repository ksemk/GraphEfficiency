/**
 * @file GraphsGenerating.h
 * @brief This file contains the declaration of the GraphsGenerating class.
 */

#ifndef GRAPHEFFICIENCY_GRAPHSGENERATING_H
#define GRAPHEFFICIENCY_GRAPHSGENERATING_H

/**
 * @struct slistEl
 * @brief A struct representing an element in a singly linked list.
 *
 * This struct represents an element in a singly linked list, which is used to implement an adjacency list for a graph.
 * Each element contains a pointer to the next element, an integer representing a vertex, and an integer representing the weight of the edge to that vertex.
 */
struct slistEl {
    slistEl *next; ///< Pointer to the next element in the list
    int v; ///< The vertex this element represents
    int weight; ///< The weight of the edge to the vertex
};

/**
 * @class GraphsGenerating
 * @brief A class for generating and manipulating graphs.
 *
 * This class provides static methods for loading a graph from a file, printing the adjacency matrix and list of the graph, generating a random graph, and freeing the memory used by the graph.
 * The graph is represented as both an adjacency matrix and an adjacency list.
 * The number of vertices and edges in the graph are also stored.
 */
class GraphsGenerating {
public:
    static int **adjMatrix; ///< Adjacency matrix representation of the graph
    static int numVertices; ///< Number of vertices in the graph
    static int numEdges; ///< Number of edges in the graph
    static slistEl **adjList; ///< Adjacency list representation of the graph

    /**
     * @brief Loads a graph from a file.
     *
     * This function reads a graph from a file and stores it in both adjacency matrix and adjacency list formats.
     * The file should contain the number of edges and vertices on the first line, followed by lines containing the start vertex, end vertex, and weight of each edge.
     */
    static void loadGraphFromFile();

    /**
     * @brief Prints the adjacency matrix of the graph.
     *
     * This function prints the adjacency matrix representation of the graph to the console.
     */
    static void printAdjacencyMatrix();

    /**
     * @brief Prints the adjacency list of the graph.
     *
     * This function prints the adjacency list representation of the graph to the console.
     */
    static void printAdjacencyList();

    /**
     * @brief Generates a random graph.
     *
     * This function generates a random graph with a given number of vertices and density.
     * The density is a percentage that determines the number of edges in the graph.
     * The graph is stored in both adjacency matrix and adjacency list formats.
     *
     * @param vertices The number of vertices in the graph.
     * @param density The density of the graph, as a percentage.
     */
    static void generateRandomGraph(int vertices, int density);

    /**
     * @brief Frees the memory used by the adjacency matrix and list.
     *
     * This function deletes the adjacency matrix and list and sets their pointers to nullptr.
     */
    static void freeMemory();
};

#endif //GRAPHEFFICIENCY_GRAPHSGENERATING_H