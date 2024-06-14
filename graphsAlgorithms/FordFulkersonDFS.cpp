#include "FordFulkersonDFS.h"
#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

bool FordFulkersonDFS::dfsIncMatrix(int **residualGraph, int source, int sink, int parent[], int numVertices, int numEdges) {
    bool *visited = new bool[numVertices](); // Initialize with false
    int *stack = new int[numVertices];
    int top = -1;
    stack[++top] = source;
    visited[source] = true;
    parent[source] = -1;

    while (top != -1) {
        int u = stack[top--];

        for (int e = 0; e < numEdges; e++) {
            if (residualGraph[u][e] > 0) {
                int v = -1;
                for (int i = 0; i < numVertices; i++) {
                    if (i != u && residualGraph[i][e] < 0) {
                        v = i;
                        break;
                    }
                }
                if (v != -1 && !visited[v]) {
                    if (v == sink) {
                        parent[v] = u;
                        delete[] visited;
                        delete[] stack;
                        return true;
                    }
                    stack[++top] = v;
                    visited[v] = true;
                    parent[v] = u;
                }
            }
        }
    }
    delete[] visited;
    delete[] stack;
    return false;
}

int FordFulkersonDFS::AlgorithmCalculationFromIncMatrix(int **incMatrix, int source, int sink, int numVertices, int numEdges) {
    int **residualGraph = new int *[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        residualGraph[i] = new int[numEdges];
        for (int j = 0; j < numEdges; ++j) {
            residualGraph[i][j] = incMatrix[i][j];
        }
    }

    int *parent = new int[numVertices];
    int maxFlow = 0;

    while (dfsIncMatrix(residualGraph, source, sink, parent, numVertices, numEdges)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (int e = 0; e < numEdges; e++) {
                if (residualGraph[u][e] > 0 && residualGraph[v][e] < 0) {
                    pathFlow = min(pathFlow, residualGraph[u][e]);
                    break;
                }
            }
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (int e = 0; e < numEdges; e++) {
                if (residualGraph[u][e] > 0 && residualGraph[v][e] < 0) {
                    residualGraph[u][e] -= pathFlow;
                    residualGraph[v][e] += pathFlow;
                    break;
                }
            }
        }

        maxFlow += pathFlow;
    }

    for (int i = 0; i < numVertices; ++i) {
        delete[] residualGraph[i];
    }
    delete[] residualGraph;
    delete[] parent;

    return maxFlow;
}

void FordFulkersonDFS::PrintResults(int maxFlow, double elapsed, int **residualGraph, int numVertices, int numEdges) {
    printf("Elapsed time: %.3f ms\n", elapsed);
    printf("Residual Graph:\n");
    for (int u = 0; u < numVertices; ++u) {
        for (int e = 0; e < numEdges; ++e) {
            if (residualGraph[u][e] > 0) {
                for (int v = 0; v < numVertices; ++v) {
                    if (v != u && residualGraph[v][e] < 0) {
                        printf("%-4d -> %-4d with flow %-4d\n", u, v, residualGraph[u][e]);
                        break;
                    }
                }
            }
        }
    }
    printf("Max Flow: %d\n", maxFlow);
}

bool FordFulkersonDFS::dfsList(slistEl **residualGraph, int source, int sink, int parent[], int numVertices) {
    bool *visited = new bool[numVertices](); // Initialize with false
    int *stack = new int[numVertices];
    int top = -1;
    stack[++top] = source;
    visited[source] = true;
    parent[source] = -1;

    while (top != -1) {
        int u = stack[top--];

        for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
            int v = p->v;
            if (!visited[v] && p->weight > 0) {
                if (v == sink) {
                    parent[v] = u;
                    delete[] visited;
                    delete[] stack;
                    return true;
                }
                stack[++top] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    delete[] visited;
    delete[] stack;
    return false;
}

int FordFulkersonDFS::AlgorithmCalculationFromList(slistEl **graph, int source, int sink, int numVertices) {
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

    while (dfsList(residualGraph, source, sink, parent, numVertices)) {
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

void FordFulkersonDFS::PrintResultsList(int maxFlow, double elapsed, slistEl **residualGraph, int numVertices) {
    printf("Elapsed time: %.3f ms\n", elapsed);
    printf("Residual Graph:\n");
    for (int u = 0; u < numVertices; ++u) {
        for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
            if (p->weight > 0) {
                printf("%-4d -> %-4d with flow %-4d\n", u, p->v, p->weight);
            }
        }
    }
    printf("Max Flow: %d\n", maxFlow);
}

void FordFulkersonDFS::TimeCounterIncMatrix(int **incMatrix, int source, int sink, int numVertices, int numEdges) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;

    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        int maxFlow = AlgorithmCalculationFromIncMatrix(incMatrix, source, sink, numVertices, numEdges);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            PrintResults(maxFlow, elapsed.count() * 1000, incMatrix, numVertices, numEdges);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
    }

    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}void FordFulkersonDFS::TimeCounterList(slistEl **graph, int source, int sink, int numVertices) {
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
            PrintResultsList(maxFlow, elapsed.count() * 1000, graph, numVertices);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
    }

    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}