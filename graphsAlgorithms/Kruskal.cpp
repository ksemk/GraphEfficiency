#include "Kruskal.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

vector<Kruskal::Edge> Kruskal::mst;

// Find set of an element i (uses path compression technique)
int Kruskal::find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]);
}

// A function that does union of two sets of x and y (uses union by rank)
void Kruskal::Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Function to sort edges in non-decreasing order of their weight
void Kruskal::sortEdges(vector<Edge>& edges) {
    for (size_t i = 0; i < edges.size() - 1; i++) {
        for (size_t j = 0; j < edges.size() - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                swap(edges[j], edges[j + 1]);
            }
        }
    }
}

int Kruskal::AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int numEdges) {
    vector<Edge> edges;
    for (int u = 0; u < numVertices; ++u) {
        for (int v = u + 1; v < numVertices; ++v) {
            if (adjMatrix[u][v] != 0) {
                edges.push_back({u, v, adjMatrix[u][v]});
            }
        }
    }

    sortEdges(edges);

    int *parent = new int[numVertices];
    int *rank = new int[numVertices];

    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mstWeight = 0;
    mst.clear(); // Clear the mst vector

    for (const Edge &edge : edges) {
        int x = find(parent, edge.src);
        int y = find(parent, edge.dest);

        if (x != y) {
            mstWeight += edge.weight;
            Union(parent, rank, x, y);
            mst.push_back(edge); // Store the edge in the MST
        }
    }

    delete[] parent;
    delete[] rank;

    return mstWeight;
}

int Kruskal::AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int numEdges) {
    vector<Edge> edges;
    for (int u = 0; u < numVertices; ++u) {
        for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
            if (u < p->v) { // To avoid duplicates
                edges.push_back({u, p->v, p->weight});
            }
        }
    }

    sortEdges(edges);

    int *parent = new int[numVertices];
    int *rank = new int[numVertices];

    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mstWeight = 0;
    mst.clear(); // Clear the mst vector

    for (const Edge &edge : edges) {
        int x = find(parent, edge.src);
        int y = find(parent, edge.dest);

        if (x != y) {
            mstWeight += edge.weight;
            Union(parent, rank, x, y);
            mst.push_back(edge); // Store the edge in the MST
        }
    }

    delete[] parent;
    delete[] rank;

    return mstWeight;
}

void Kruskal::PrintResults(int mstWeight, double elapsed) {
    printf("Minimum Spanning Tree Weight: %d\n", mstWeight);
    printf("%-10s %-10s\n", "Edge", "Weight");
    for (const auto& edge : mst)
        printf("%-4d - %-4d \t%-4d\n", edge.src, edge.dest, edge.weight);
    printf("Elapsed time: %.3f ms\n", elapsed);
}

void Kruskal::TimeCounterMatrix(int **adjMatrix, int numVertices, int numEdges) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        int mstWeight = AlgorithmCalculationFromMatrix(adjMatrix, numVertices, numEdges);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            PrintResults(mstWeight, elapsed.count() * 1000);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}

void Kruskal::TimeCounterList(slistEl **adjList, int numVertices, int numEdges) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        int mstWeight = AlgorithmCalculationFromList(adjList, numVertices, numEdges);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            PrintResults(mstWeight, elapsed.count() * 1000);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}
