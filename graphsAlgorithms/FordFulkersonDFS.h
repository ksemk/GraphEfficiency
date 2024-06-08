#ifndef FORDFULKERSONDFS_H
#define FORDFULKERSONDFS_H

#include "../GraphsGenerating.h"

class FordFulkersonDFS {
public:
    static bool dfs(int **residualGraph, int source, int sink, int parent[], int numVertices);
    static bool dfsList(slistEl **residualGraph, int source, int sink, int parent[], int numVertices);
    static int AlgorithmCalculationFromMatrix(int **graph, int source, int sink, int numVertices);
    static int AlgorithmCalculationFromList(slistEl **graph, int source, int sink, int numVertices);
    static void PrintResults(int maxFlow, double elapsed, int **residualGraph, int numVertices);
    static void PrintResultsList(int maxFlow, double elapsed, slistEl **residualGraph, int numVertices);
    static void TimeCounterMatrix(int **graph, int source, int sink, int numVertices);
    static void TimeCounterList(slistEl **graph, int source, int sink, int numVertices);
};

#endif
