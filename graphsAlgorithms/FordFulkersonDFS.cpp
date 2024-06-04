#include "FordFulkersonDFS.h"
#include <iostream>
#include <climits>
#include <stack>
#include <chrono>

using namespace std;

bool FordFulkersonDFS::dfs(int **residualGraph, int source, int sink, int parent[], int numVertices) {
    bool *visited = new bool[numVertices](); // Initialize with false
    stack<int> stack;
    stack.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == sink) {
                    parent[v] = u;
                    delete[] visited;
                    return true;
                }
                stack.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    delete[] visited;
    return false;
}

bool FordFulkersonDFS::dfsList(slistEl **residualGraph, int source, int sink, int parent[], int numVertices) {
    bool *visited = new bool[numVertices](); // Initialize with false
    stack<int> stack;
    stack.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();

        for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
            int v = p->v;
            if (!visited[v] && p->weight > 0) {
                if (v == sink) {
                    parent[v] = u;
                    delete[] visited;
                    return true;
                }
                stack.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    delete[] visited;
    return false;
}

int FordFulkersonDFS::AlgorithmCalculationFromMatrix(int **graph, int source, int sink, int numVertices) {
    int **residualGraph = new int *[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        residualGraph[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            residualGraph[i][j] = graph[i][j];
        }
    }

    int *parent = new int[numVertices];
    int maxFlow = 0;

    while (dfs(residualGraph, source, sink, parent, numVertices)) {
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

    for (int i = 0; i < numVertices; ++i) {
        delete[] residualGraph[i];
    }
    delete[] residualGraph;
    delete[] parent;

    return maxFlow;
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

void FordFulkersonDFS::PrintResults(int maxFlow, double elapsed) {
    cout << "Max Flow: " << maxFlow << endl;
    cout << "Elapsed time: " << elapsed << " ms" << endl;
}

void FordFulkersonDFS::PrintResultsList(int maxFlow, double elapsed, slistEl **residualGraph, int numVertices) {
    cout << "Max Flow: " << maxFlow << endl;
    cout << "Elapsed time: " << elapsed << " ms" << endl;
    cout << "Residual Graph:" << endl;
    for (int u = 0; u < numVertices; ++u) {
        for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
            if (p->weight > 0) {
                cout << u << " -> " << p->v << " with flow " << p->weight << endl;
            }
        }
    }
}

void FordFulkersonDFS::TimeCounterMatrix(int **graph, int source, int sink, int numVertices) {
    auto start = chrono::high_resolution_clock::now();
    int maxFlow = AlgorithmCalculationFromMatrix(graph, source, sink, numVertices);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    PrintResults(maxFlow, elapsed.count() * 1000);
}

void FordFulkersonDFS::TimeCounterList(slistEl **graph, int source, int sink, int numVertices) {
    auto start = chrono::high_resolution_clock::now();
    int maxFlow = AlgorithmCalculationFromList(graph, source, sink, numVertices);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    PrintResultsList(maxFlow, elapsed.count() * 1000, graph, numVertices);
}
