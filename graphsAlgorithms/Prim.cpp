#include "Prim.h"
#include "../GraphsGenerating.h"
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <climits>

using namespace std;

vector<Prim::Edge> Prim::mst;

int Prim::AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices) {
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    vector<bool> inMST(numVertices, false);
    vector<int> key(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    int mstWeight = 0;

    pq.push({-1, 0, 0}); // Start with vertex 0
    key[0] = 0;

    while (!pq.empty()) {
        int u = pq.top().dest; // Get the destination vertex
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mstWeight += key[u];

        for (int v = 0; v < numVertices; ++v) {
            if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                key[v] = adjMatrix[u][v];
                pq.push({u, v, key[v]});
                parent[v] = u;
            }
        }
    }

    mst.clear();
    for (int i = 1; i < numVertices; ++i) {
        if (parent[i] != -1) {
            mst.push_back({parent[i], i, adjMatrix[parent[i]][i]});
        }
    }

    return mstWeight;
}

int Prim::AlgorithmCalculationFromList(slistEl **adjList, int numVertices) {
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    vector<bool> inMST(numVertices, false);
    vector<int> key(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    int mstWeight = 0;

    pq.push({-1, 0, 0}); // Start with vertex 0
    key[0] = 0;

    while (!pq.empty()) {
        int u = pq.top().dest; // Get the destination vertex
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mstWeight += key[u];

        for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
            int v = p->v;
            int weight = p->weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({u, v, key[v]});
                parent[v] = u;
            }
        }
    }

    mst.clear();
    for (int i = 1; i < numVertices; ++i) {
        if (parent[i] != -1) {
            mst.push_back({parent[i], i, key[i]});
        }
    }

    return mstWeight;
}

void Prim::PrintResults(int mstWeight, double elapsed) {
    cout << "Minimum Spanning Tree Weight: " << mstWeight << endl;
    cout << "Edge \tWeight\n";
    for (const auto& edge : mst)
        cout << edge.src << " - " << edge.dest << " \t" << edge.weight << " \n";
    cout << "Elapsed time: " << elapsed << " ms" << endl;
}

void Prim::TimeCounterMatrix(int **adjMatrix, int numVertices) {
    auto start = chrono::high_resolution_clock::now();
    int mstWeight = AlgorithmCalculationFromMatrix(adjMatrix, numVertices);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    PrintResults(mstWeight, elapsed.count() * 1000);
}

void Prim::TimeCounterList(slistEl **adjList, int numVertices) {
    auto start = chrono::high_resolution_clock::now();
    int mstWeight = AlgorithmCalculationFromList(adjList, numVertices);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    PrintResults(mstWeight, elapsed.count() * 1000);
}
