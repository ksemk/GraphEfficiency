/**
 * @file Prim.h
 * @brief This file contains the declaration of the Prim class.
 */

#ifndef PRIM_H
#define PRIM_H

#include "../GraphsGenerating.h" // Ensure this path is correct and accessible

class Prim {
public:
    struct Edge {
        int src; // The source vertex of the edge
        int dest; // The destination vertex of the edge
        int weight; // The weight of the edge
    };

    // Function declarations
    static int AlgorithmCalculationFromMatrix(int **incMatrix, int numVertices, int numEdges);
    static int AlgorithmCalculationFromList(slistEl **adjList, int numVertices);
    static void PrintResults(int mstWeight, double elapsed);
    static void TimeCounterMatrix(int **incMatrix, int numVertices, int numEdges);
    static void TimeCounterList(slistEl **adjList, int numVertices);
    static int minKey(int* key, bool* inMST, int numVertices); // Ensure this is declared as static and matches the definition

private:
    static Edge* mst; // The resulting MST, stored as an array of edges
    static int mstSize; // Size of the MST array
};

#endif
