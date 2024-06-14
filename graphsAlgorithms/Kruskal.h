/**
 * @file Kruskal.h
 * @brief This file contains the declaration of the Kruskal class.
 */

#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../GraphsGenerating.h"
#include <vector>

class Kruskal {
public:
    struct Edge {
        int src;
        int dest;
        int weight;
    };

    // Function declarations
    static int AlgorithmCalculationFromMatrix(int **incMatrix, int numVertices, int numEdges);
    static int AlgorithmCalculationFromList(slistEl **adjList, int numVertices);
    static void PrintResults(int mstWeight, double elapsed);
    static void TimeCounterMatrix(int **incMatrix, int numVertices, int numEdges);
    static void TimeCounterList(slistEl **adjList, int numVertices);
    static int find(int parent[], int i);
    static void Union(int parent[], int rank[], int x, int y);
    static void sortEdges(std::vector<Edge>& edges);

private:
    static std::vector<Edge> mst; // The resulting MST, stored as a vector of edges
};

#endif
