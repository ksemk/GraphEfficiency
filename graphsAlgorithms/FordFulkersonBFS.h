#ifndef FORDFULKERSONBFS_H
#define FORDFULKERSONBFS_H
#include "../GraphsGenerating.h"

class FordFulkersonBFS {
public:
    static bool bfsIncMatrix(int **incMatrix, int source, int sink, int parent[], int numVertices, int numEdges);
    static int AlgorithmCalculationFromIncMatrix(int **incMatrix, int source, int sink, int numVertices, int numEdges);
    static void PrintResults(int maxFlow, double elapsed, int **residualGraph, int numVertices);
    static void TimeCounterIncMatrix(int **incMatrix, int source, int sink, int numVertices, int numEdges);

    static bool bfsList(slistEl **residualGraph, int source, int sink, int parent[], int numVertices);
    static int AlgorithmCalculationFromList(slistEl **graph, int source, int sink, int numVertices);
    static void PrintResultsList(int maxFlow, slistEl **residualGraph, int numVertices);
    static void TimeCounterList(slistEl **graph, int source, int sink, int numVertices);
};

#endif