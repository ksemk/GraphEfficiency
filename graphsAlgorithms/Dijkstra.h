#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <utility>
#include "../GraphsGenerating.h"


class PriorityQueue {
public:
    PriorityQueue(int capacity, int* dist);
    ~PriorityQueue();
    void push(int v);
    int pop();
    bool isEmpty();
    void decreaseKey(int v);

private:
    void heapify(int idx);
    void swap(int* a, int* b);
    int* heap;
    int* pos;
    int size;
    int capacity;
    int* dist;
};

class Dijkstra {
public:
    static std::pair<int*, int*> AlgorithmCalculationFromMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex);
    static std::pair<int*, int*> AlgorithmCalculationFromList(slistEl** adjList, int numVertices, int startVertex);
    static void PrintResults(int* dist, int* prev, int numVertices, int startVertex);
    static void TimeCounterList(slistEl** adjList, int numVertices, int startVertex);
    static void TimeCounterMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex);
};

#endif
