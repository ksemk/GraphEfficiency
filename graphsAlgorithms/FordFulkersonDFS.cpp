/**
 * @file FordFulkersonDFS.cpp
 * @brief This file contains the implementation of the FordFulkersonDFS class.
 */

#include "FordFulkersonDFS.h"
#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

/**
 * @brief Performs a DFS on the residual graph and returns true if there is a path from source to sink.
 *
 * @param residualGraph The residual graph.
 * @param source The source vertex.
 * @param sink The sink vertex.
 * @param parent The parent array.
 * @param numVertices The number of vertices in the graph.
 * @return True if there is a path from source to sink, false otherwise.
 */
bool FordFulkersonDFS::dfs(int **residualGraph, int source, int sink, int parent[], int numVertices) {
    bool *visited = new bool[numVertices](); // Initialize with false
    int *stack = new int[numVertices];
    int top = -1;
    stack[++top] = source;
    visited[source] = true;
    parent[source] = -1;

    while (top != -1) {
        int u = stack[top--];

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
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

/**
 * @brief Performs a DFS on the residual graph (represented as an adjacency list) and returns true if there is a path from source to sink.
 *
 * @param residualGraph The residual graph.
 * @param source The source vertex.
 * @param sink The sink vertex.
 * @param parent The parent array.
 * @param numVertices The number of vertices in the graph.
 * @return True if there is a path from source to sink, false otherwise.
 */
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

/**
 * @brief Runs the Ford-Fulkerson algorithm on a graph represented as an adjacency matrix.
 *
 * @param graph The graph.
 * @param source The source vertex.
 * @param sink The sink vertex.
 * @param numVertices The number of vertices in the graph.
 * @return The maximum flow.
 */
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

    PrintResults(maxFlow, 0, residualGraph, numVertices);  // No elapsed time calculation here

    for (int i = 0; i < numVertices; ++i) {
        delete[] residualGraph[i];
    }
    delete[] residualGraph;
    delete[] parent;

    return maxFlow;
}

/**
 * @brief Runs the Ford-Fulkerson algorithm on a graph represented as an adjacency list.
 *
 * @param graph The graph.
 * @param source The source vertex.
 * @param sink The sink vertex.
 * @param numVertices The number of vertices in the graph.
 * @return The maximum flow.
 */
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

    PrintResultsList(maxFlow, 0, residualGraph, numVertices);  // No elapsed time calculation here

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

/**
 * @brief Prints the results of the Ford-Fulkerson algorithm.
 *
 * @param maxFlow The maximum flow.
 * @param elapsed The time taken by the algorithm, in seconds.
 * @param residualGraph The residual graph.
 * @param numVertices The number of vertices in the graph.
 */
void FordFulkersonDFS::PrintResults(int maxFlow, double elapsed, int **residualGraph, int numVertices) {
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

/**
 * @brief Prints the results of the Ford-Fulkerson algorithm for a graph represented as an adjacency list.
 *
 * @param maxFlow The maximum flow.
 * @param elapsed The time taken by the algorithm, in seconds.
 * @param residualGraph The residual graph.
 * @param numVertices The number of vertices in the graph.
 */
void FordFulkersonDFS::PrintResultsList(int maxFlow, double elapsed, slistEl **residualGraph, int numVertices) {
    printf("Max Flow: %d\n", maxFlow);
    printf("Elapsed time: %.3f ms\n", elapsed);
    printf("Residual Graph:\n");
    for (int u = 0; u < numVertices; ++u) {
        for (slistEl* p = residualGraph[u]; p != nullptr; p = p->next) {
            if (p->weight > 0) {
                printf("%-4d -> %-4d with flow %-4d\n", u, p->v, p->weight);
            }
        }
    }
}

/**
 * @brief Measures and prints the time taken by the Ford-Fulkerson algorithm on a graph represented as an adjacency matrix.
 *
 * @param graph The graph.
 * @param source The source vertex.
 * @param sink The sink vertex.
 * @param numVertices The number of vertices in the graph.
 */
void FordFulkersonDFS::TimeCounterMatrix(int **graph, int source, int sink, int numVertices) {
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

/**
 * @brief Measures and prints the time taken by the Ford-Fulkerson algorithm on a graph represented as an adjacency list.
 *
 * @param graph The graph.
 * @param source The source vertex.
 * @param sink The sink vertex.
 * @param numVertices The number of vertices in the graph.
 */
void FordFulkersonDFS::TimeCounterList(slistEl **graph, int source, int sink, int numVertices) {
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
