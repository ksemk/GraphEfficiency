#include "FordFulkersonBFS.h"
#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

bool FordFulkersonBFS::bfs(int **residualGraph, int source, int sink, int parent[], int numVertices) {
    bool *visited = new bool[numVertices]();
    int *queue = new int[numVertices];
    int front = 0, back = 0;
    queue[back++] = source;
    visited[source] = true;
    parent[source] = -1;

    while (front != back) {
        int u = queue[front++];
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == sink) {
                    parent[v] = u;
                    delete[] visited;
                    delete[] queue;
                    return true;
                }
                queue[back++] = v;
                visited[v] = true;
                parent[v] = u;
            }
        }
    }

    delete[] visited;
    delete[] queue;
    return false;
}

bool FordFulkersonBFS::bfsList(slistEl **residualGraph, int source, int sink, int parent[], int numVertices) {
    bool *visited = new bool[numVertices]();
    int *queue = new int[numVertices];
    int front = 0, back = 0;
    queue[back++] = source;
    visited[source] = true;
    parent[source] = -1;

    while (front != back) {
        int u = queue[front++];
        for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
            int v = p->v;
            if (!visited[v] && p->weight > 0) {
                if (v == sink) {
                    parent[v] = u;
                    delete[] visited;
                    delete[] queue;
                    return true;
                }
                queue[back++] = v;
                visited[v] = true;
                parent[v] = u;
            }
        }
    }

    delete[] visited;
    delete[] queue;
    return false;
}

int FordFulkersonBFS::AlgorithmCalculationFromMatrix(int **graph, int source, int sink, int numVertices) {
    int **residualGraph = new int *[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        residualGraph[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            residualGraph[i][j] = graph[i][j];
        }
    }

    int *parent = new int[numVertices];
    int maxFlow = 0;

    while (bfs(residualGraph, source, sink, parent, numVertices)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    PrintResults(maxFlow, 0, residualGraph, numVertices);  // No elapsed time calculation here

    for (int i = 0; i < numVertices; ++i) {
        delete[] residualGraph[i];
    }
    delete[] residualGraph;
    delete[] parent;

    return maxFlow;
}

int FordFulkersonBFS::AlgorithmCalculationFromList(slistEl **graph, int source, int sink, int numVertices) {
    slistEl **residualGraph = new slistEl *[numVertices];
    for (int u = 0; u < numVertices; u++) {
        residualGraph[u] = nullptr;
        for (slistEl* p = graph[u]; p != nullptr; p = p->next) {
            slistEl *newEl = new slistEl;
            newEl->v = p->v;
            newEl->weight = p->weight;
            newEl->next = residualGraph[u];
            residualGraph[u] = newEl;
        }
    }

    int *parent = new int[numVertices];
    int maxFlow = 0;

    while (bfsList(residualGraph, source, sink, parent, numVertices)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
                if (p->v == v) {
                    pathFlow = min(pathFlow, p->weight);
                }
            }
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
                if (p->v == v) {
                    p->weight -= pathFlow;
                }
            }
            for (slistEl* p = residualGraph[v]; p != nullptr; p = p->next) {
                if (p->v == u) {
                    p->weight += pathFlow;
                }
            }
        }

        maxFlow += pathFlow;
    }
    for (int i = 0; i < numVertices; i++) {
        slistEl* p = residualGraph[i];
        while (p != nullptr) {
            slistEl* temp = p;
            p = p->next;
            delete temp;
        }
    }
    delete[] residualGraph;
    delete[] parent;

    return maxFlow;
}

void FordFulkersonBFS::PrintResults(int maxFlow, double elapsed, int **residualGraph, int numVertices) {
    printf("Max Flow: %d\n", maxFlow);
    printf("Elapsed time: %.3f ms\n", elapsed);
    printf("Residual Graph:\n");
    for (int u = 0; u < numVertices; ++u) {
        for (int v = 0; v < numVertices; ++v) {
            if (residualGraph[u][v] > 0) {
                printf("%-4d -> %-4d with flow %-4d\n", u, v, residualGraph[u][v]);
            }
        }
    }
}

void FordFulkersonBFS::PrintResultsList(int maxFlow, slistEl **residualGraph, int numVertices) {
    printf("Max Flow: %d\n", maxFlow);
    printf("Residual Graph:\n");
    for (int u = 0; u < numVertices; ++u) {
        for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
            if (p->weight > 0) {
                printf("%-4d -> %-4d with flow %-4d\n", u, p->v, p->weight);
            }
        }
    }
}

void FordFulkersonBFS::TimeCounterMatrix(int **graph, int source, int sink, int numVertices) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        int maxFlow = AlgorithmCalculationFromMatrix(graph, source, sink, numVertices);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            PrintResults(maxFlow, elapsed.count() * 1000, graph, numVertices);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}

void FordFulkersonBFS::TimeCounterList(slistEl **graph, int source, int sink, int numVertices) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        int maxFlow = AlgorithmCalculationFromList(graph, source, sink, numVertices);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            PrintResultsList(maxFlow, graph, numVertices);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}
