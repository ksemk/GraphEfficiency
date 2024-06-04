#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../GraphsGenerating.h"
#include <vector>

class Kruskal {
public:
    static int AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int numEdges); // Run Kruskal's algorithm from matrix
    static int AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int numEdges); // Run Kruskal's algorithm from list
    static void PrintResults(int mstWeight, double elapsed); // Print the results
    static void TimeCounterMatrix(int **adjMatrix, int numVertices, int numEdges); // Measure and print the time taken by the algorithm from matrix
    static void TimeCounterList(slistEl **adjList, int numVertices, int numEdges); // Measure and print the time taken by the algorithm from list

private:
    struct Edge {
        int src, dest, weight;
    };

    static int find(int parent[], int i);
    static void Union(int parent[], int rank[], int x, int y);

    static std::vector<Edge> mst; // Store the resulting MST
};

#endif // KRUSKAL_H
