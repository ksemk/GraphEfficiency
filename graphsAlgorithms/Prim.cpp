/**
 * @file Prim.cpp
 * @brief This file contains the implementation of the Prim class.
 */

#include "Prim.h"
#include "../GraphsGenerating.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <climits>

using namespace std;

// The resulting MST, stored as a vector of edges
vector<Prim::Edge> Prim::mst;


/**
 * @brief Finds the vertex with the minimum key value, from the set of vertices not yet included in the MST.
 *
 * @param key The key values of the vertices.
 * @param inMST A boolean vector indicating whether each vertex is included in the MST.
 * @param numVertices The number of vertices in the graph.
 * @return The index of the vertex with the minimum key value.
 */
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

/**
 * @brief Runs Prim's algorithm on a graph represented as an adjacency matrix.
 *
 * @param adjMatrix The adjacency matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @return The total weight of the MST.
 */
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

/**
 * @brief Runs Prim's algorithm on a graph represented as an adjacency list.
 *
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @return The total weight of the MST.
 */
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

/**
 * @brief Prints the results of Prim's algorithm.
 *
 * @param mstWeight The total weight of the MST.
 * @param elapsed The time taken by the algorithm, in seconds.
 */
void Prim::PrintResults(int mstWeight, double elapsed) {
    printf("Minimum Spanning Tree Weight: %d\n", mstWeight);
    printf("%-10s %-10s\n", "Edge", "Weight");
    for (const auto& edge : mst)
        printf("%-4d - %-4d \t%-4d\n", edge.src, edge.dest, edge.weight);
    printf("Elapsed time: %.3f ms\n", elapsed);
}

/**
 * @brief Measures and prints the time taken by Prim's algorithm on a graph represented as an adjacency matrix.
 *
 * @param adjMatrix The adjacency matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 */
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

/**
 * @brief Measures and prints the time taken by Prim's algorithm on a graph represented as an adjacency list.
 *
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 */
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
