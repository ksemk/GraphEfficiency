//
// Created by 10122 on 01.06.2024.
//

#ifndef GRAPHEFFICIENCY_BELLMANFORD_H
#define GRAPHEFFICIENCY_BELLMANFORD_H

#include "../GraphsGenerating.h"
#include <utility>

class BellmanFord {
public:
    static std::pair<int*, int*> AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int startVertex);
    static std::pair<int*, int*> AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int startVertex);
    static void PrintResults(int *dist, int *prev, int numVertices, int startVertex);
    static void TimeCounterMatrix(int **adjMatrix, int numVertices, int startVertex);
    static void TimeCounterList(slistEl **adjList, int numVertices, int startVertex);
};

#endif //GRAPHEFFICIENCY_BELLMANFORD_H
