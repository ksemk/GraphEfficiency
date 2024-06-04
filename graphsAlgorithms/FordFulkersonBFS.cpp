#include "FordFulkersonBFS.h"
#include <iostream>
#include <climits>
#include <queue>
#include <chrono>

using namespace std;

bool FordFulkersonBFS::bfs(int **residualGraph, int source, int sink, int parent[], int numVertices) {
    // Initialize visited array to keep track of visited nodes
    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i)
        visited[i] = false;

    // Queue for BFS
    int *queue = new int[numVertices];
    int front = 0, back = 0;
    queue[back++] = source;
    visited[source] = true;
    parent[source] = -1;

    // Standard BFS loop
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
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    delete[] visited;
    delete[] queue;
    return false;
}


bool FordFulkersonBFS::bfsList(slistEl **residualGraph, int source, int sink, int parent[], int numVertices) {
    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i)
        visited[i] = false;

    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
            int v = p->v;
            if (!visited[v] && p->weight > 0) {
                if (v == sink) {
                    parent[v] = u;
                    delete[] visited;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    delete[] visited;
    return false;
}

int FordFulkersonBFS::AlgorithmCalculationFromMatrix(int **graph, int source, int sink, int numVertices) {
    // Create a residual graph and fill the residual graph with given capacities in the original graph
    int **residualGraph = new int *[numVertices];
    for (int u = 0; u < numVertices; u++) {
        residualGraph[u] = new int[numVertices];
        for (int v = 0; v < numVertices; v++) {
            residualGraph[u][v] = graph[u][v];
        }
    }

    // Array to store the path found by BFS
    int *parent = new int[numVertices];
    int maxFlow = 0;  // Initialize max flow

    // Augment the flow while there is a path from source to sink
    while (bfs(residualGraph, source, sink, parent, numVertices)) {
        // Find the maximum flow through the path found by BFS
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Add the path flow to the overall flow
        maxFlow += pathFlow;
    }

    // Clean up memory
    for (int i = 0; i < numVertices; i++) {
        delete[] residualGraph[i];
    }
    delete[] residualGraph;
    delete[] parent;

    return maxFlow;
}

int FordFulkersonBFS::AlgorithmCalculationFromList(slistEl **graph, int source, int sink, int numVertices) {
    int u, v;

    slistEl **residualGraph = new slistEl *[numVertices];
    for (u = 0; u < numVertices; u++) {
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
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
                if (p->v == v) {
                    pathFlow = min(pathFlow, p->weight);
                }
            }
        }

        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
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

void FordFulkersonBFS::PrintResults(int maxFlow, double elapsed) {
    cout << "Max Flow: " << maxFlow << endl;
    cout << "Elapsed time: " << elapsed << " ms" << endl;
}

void FordFulkersonBFS::PrintResultsList(int maxFlow, double elapsed, slistEl **residualGraph, int numVertices) {
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

void FordFulkersonBFS::TimeCounterMatrix(int **graph, int source, int sink, int numVertices) {
    auto start = chrono::high_resolution_clock::now();
    int maxFlow = AlgorithmCalculationFromMatrix(graph, source, sink, numVertices);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    PrintResults(maxFlow, elapsed.count() * 1000);
}

void FordFulkersonBFS::TimeCounterList(slistEl **graph, int source, int sink, int numVertices) {
    auto start = chrono::high_resolution_clock::now();
    int maxFlow = AlgorithmCalculationFromList(graph, source, sink, numVertices);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    PrintResultsList(maxFlow, elapsed.count() * 1000, graph, numVertices);
}
