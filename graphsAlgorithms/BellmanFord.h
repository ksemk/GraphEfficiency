#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <utility>
#include "../GraphsGenerating.h"

class BellmanFord {
public:
    static std::pair<int*, int*> AlgorithmCalculationFromMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex);
    static std::pair<int*, int*> AlgorithmCalculationFromList(slistEl** adjList, int numVertices, int startVertex);
    static void PrintResults(int* dist, int* prev, int numVertices, int startVertex);
    static void TimeCounterMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex);
    static void TimeCounterList(slistEl** adjList, int numVertices, int startVertex);
};

#endif
