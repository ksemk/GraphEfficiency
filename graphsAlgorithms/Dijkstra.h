//
// Created by 10122 on 01.06.2024.
//

#ifndef GRAPHEFFICIENCY_DIJKSTRA_H
#define GRAPHEFFICIENCY_DIJKSTRA_H

#include <utility>
#include "../GraphsGenerating.h"

using namespace std;

class Dijkstra {

public:
    static pair<int*, int*> AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int startVertex);
    static pair<int*, int*> AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int startVertex);
    static void PrintResults(int *dist, int *prev, int numVertices, int startVertex);
    static void TimeCounterMatrix(int **adjMatrix, int numVertices, int startVertex);
    static void TimeCounterList(slistEl **adjList, int numVertices, int startVertex);
};

class PriorityQueue {
private:
    int* heap;
    int* pos;
    int* dist;
    int size;
    int capacity;

    void heapify(int idx);
    void swap(int* a, int* b);

public:
    PriorityQueue(int capacity, int* dist);
    ~PriorityQueue();
    void push(int v);
    int pop();
    bool isEmpty();
};

#endif //GRAPHEFFICIENCY_DIJKSTRA_H
