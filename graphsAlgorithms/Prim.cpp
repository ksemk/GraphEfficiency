#include "Prim.h"
#include "../GraphsGenerating.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <climits>

using namespace std;

vector<Prim::Edge> Prim::mst;

int Prim::minKey(const vector<int>& key, const vector<bool>& inMST, int numVertices) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < numVertices; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

int Prim::AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices) {
    vector<int> key(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    vector<bool> inMST(numVertices, false);
    key[0] = 0;
    int mstWeight = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, inMST, numVertices);
        inMST[u] = true;
        mstWeight += key[u];

        for (int v = 0; v < numVertices; v++) {
            if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = adjMatrix[u][v];
            }
        }
    }

    mst.clear();
    for (int i = 1; i < numVertices; i++) {
        if (parent[i] != -1) {
            mst.push_back({parent[i], i, adjMatrix[parent[i]][i]});
        }
    }

    return mstWeight;
}

int Prim::AlgorithmCalculationFromList(slistEl **adjList, int numVertices) {
    vector<int> key(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    vector<bool> inMST(numVertices, false);
    key[0] = 0;
    int mstWeight = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, inMST, numVertices);
        inMST[u] = true;
        mstWeight += key[u];

        for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
            int v = p->v;
            int weight = p->weight;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    mst.clear();
    for (int i = 1; i < numVertices; i++) {
        if (parent[i] != -1) {
            mst.push_back({parent[i], i, key[i]});
        }
    }

    return mstWeight;
}

void Prim::PrintResults(int mstWeight, double elapsed) {
    printf("Minimum Spanning Tree Weight: %d\n", mstWeight);
    printf("%-10s %-10s\n", "Edge", "Weight");
    for (const auto& edge : mst)
        printf("%-4d - %-4d \t%-4d\n", edge.src, edge.dest, edge.weight);
    printf("Elapsed time: %.3f ms\n", elapsed);
}

void Prim::TimeCounterMatrix(int **adjMatrix, int numVertices) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        int mstWeight = AlgorithmCalculationFromMatrix(adjMatrix, numVertices);
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

void Prim::TimeCounterList(slistEl **adjList, int numVertices) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        int mstWeight = AlgorithmCalculationFromList(adjList, numVertices);
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
