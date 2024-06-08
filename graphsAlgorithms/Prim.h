#ifndef PRIM_H
#define PRIM_H

#include <vector>
#include "../GraphsGenerating.h"

class Prim {
public:
    static int AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices); // Run Prim's algorithm from matrix
    static int AlgorithmCalculationFromList(slistEl **adjList, int numVertices); // Run Prim's algorithm from list
    static void PrintResults(int mstWeight, double elapsed); // Print the results
    static void TimeCounterMatrix(int **adjMatrix, int numVertices); // Measure and print the time taken by the algorithm from matrix
    static void TimeCounterList(slistEl **adjList, int numVertices); // Measure and print the time taken by the algorithm from list

private:
    struct Edge {
        int src, dest, weight;
    };

    static int minKey(const std::vector<int>& key, const std::vector<bool>& inMST, int numVertices);
    static std::vector<Edge> mst; // Store the resulting MST
};

#endif
