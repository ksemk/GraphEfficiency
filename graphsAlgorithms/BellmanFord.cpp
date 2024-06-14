#include "BellmanFord.h"
#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

pair<int*, int*> BellmanFord::AlgorithmCalculationFromMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex) {
    int* dist = new int[numVertices];
    int* prev = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[startVertex] = 0;

    for (int i = 1; i <= numVertices - 1; i++) {
        bool updated = false;
        for (int e = 0; e < numEdges; e++) {
            int u = -1, v = -1, weight = 0;
            for (int vertex = 0; vertex < numVertices; vertex++) {
                if (incMatrix[vertex][e] != 0) {
                    if (u == -1) {
                        u = vertex;
                        weight = incMatrix[vertex][e];
                    } else {
                        v = vertex;
                        break;
                    }
                }
            }
            if (u != -1 && v != -1) {
                if (weight < 0) {
                    std::swap(u, v);
                    weight = -weight;
                }
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }

    for (int e = 0; e < numEdges; e++) {
        int u = -1, v = -1, weight = 0;
        for (int vertex = 0; vertex < numVertices; vertex++) {
            if (incMatrix[vertex][e] != 0) {
                if (u == -1) {
                    u = vertex;
                    weight = incMatrix[vertex][e];
                } else {
                    v = vertex;
                    break;
                }
            }
        }
        if (u != -1 && v != -1) {
            if (weight < 0) {
                std::swap(u, v);
                weight = -weight;
            }
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                printf("Graph contains a negative-weight cycle\n");
                delete[] dist;
                delete[] prev;
                return make_pair(nullptr, nullptr);
            }
        }
    }

    return make_pair(dist, prev);
}

pair<int*, int*> BellmanFord::AlgorithmCalculationFromList(slistEl** adjList, int numVertices, int startVertex) {
    int* dist = new int[numVertices];
    int* prev = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[startVertex] = 0;

    for (int i = 1; i <= numVertices - 1; i++) {
        bool updated = false;
        for (int u = 0; u < numVertices; u++) {
            for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
                int v = p->v;
                int weight = p->weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }

    for (int u = 0; u < numVertices; u++) {
        for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
            int v = p->v;
            int weight = p->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                printf("Graph contains a negative-weight cycle\n");
                delete[] dist;
                delete[] prev;
                return make_pair(nullptr, nullptr);
            }
        }
    }

    return make_pair(dist, prev);
}

void BellmanFord::PrintResults(int* dist, int* prev, int numVertices, int startVertex) {
    printf("Vertex\tDistance from Source\tPath\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d\t%d\t\t\t", i, dist[i]);
        if (dist[i] != INT_MAX) {
            int pathVertex = i;
            while (pathVertex != -1) {
                if (pathVertex != startVertex) {
                    printf("%d <- ", pathVertex);
                } else {
                    printf("%d", startVertex);
                }
                pathVertex = prev[pathVertex];
            }
        }
        printf("\n");
    }
}

void BellmanFord::TimeCounterMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        pair<int*, int*> results = BellmanFord::AlgorithmCalculationFromMatrix(incMatrix, numVertices, numEdges, startVertex);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            BellmanFord::PrintResults(results.first, results.second, numVertices, startVertex);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
        delete[] results.first;
        delete[] results.second;
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}

void BellmanFord::TimeCounterList(slistEl** adjList, int numVertices, int startVertex) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        pair<int*, int*> results = BellmanFord::AlgorithmCalculationFromList(adjList, numVertices, startVertex);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            BellmanFord::PrintResults(results.first, results.second, numVertices, startVertex);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
        delete[] results.first;
        delete[] results.second;
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}
