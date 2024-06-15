#include "Prim.h"
#include <iostream>
#include <chrono>
#include <climits>

using namespace std;

// Initialize static members
Prim::Edge* Prim::mst = nullptr;
int Prim::mstSize = 0;

/**
* @brief Finds the vertex with the minimum key value, from the set of vertices not yet included in the MST
* @param key Array of key values
* @param inMST Array indicating whether a vertex is included in the MST
* @param numVertices Number of vertices in the graph
* @return Index of the vertex with the minimum key value
*/
int Prim::minKey(int* key, bool* inMST, int numVertices) {
    int min = INT_MAX, minIndex = -1;
    for (int v = 0; v < numVertices; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

/**
 * @brief Runs Prim's algorithm on a graph represented as an incidence matrix
 * @param incMatrix Incidence matrix representing the graph
 * @param numVertices Number of vertices in the graph
 * @param numEdges Number of edges in the graph
 * @return Weight of the minimum spanning tree
 */
int Prim::AlgorithmCalculationFromMatrix(int **incMatrix, int numVertices, int numEdges) {
    int* key = new int[numVertices];
    int* parent = new int[numVertices];
    bool* inMST = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }
    key[0] = 0;
    int mstWeight = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, inMST, numVertices);
        inMST[u] = true;

        for (int e = 0; e < numEdges; e++) {
            if (incMatrix[u][e] != 0) {
                int v = -1;
                int weight = abs(incMatrix[u][e]);
                for (int i = 0; i < numVertices; i++) {
                    if (i != u && incMatrix[i][e] != 0) {
                        v = i;
                        break;
                    }
                }

                if (v != -1 && !inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }
    }

    delete[] mst;  // Clear previous MST
    mst = new Edge[numVertices - 1];
    mstSize = 0;
    for (int i = 1; i < numVertices; i++) {
        if (parent[i] != -1) {
            mst[mstSize++] = {parent[i], i, key[i]};
            mstWeight += key[i];
        }
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
    return mstWeight;
}


/**
 * @brief Prints the results of Prim's algorithm
 * @param mstWeight Weight of the minimum spanning tree
 * @param elapsed Time taken by the algorithm
 */
void Prim::PrintResults(int mstWeight, double elapsed) {
    printf("Minimum Spanning Tree Weight: %d\n", mstWeight);
    printf("%-10s %-10s\n", "Edge", "Weight");
    for (int i = 0; i < mstSize; i++)
        printf("%-4d - %-4d \t%-4d\n", mst[i].src, mst[i].dest, mst[i].weight);
    printf("Elapsed time: %.3f ms\n", elapsed);
}


/**
 * @brief Measures and prints the time taken by Prim's algorithm on a graph represented as an incidence matrix
 * @param incMatrix Incidence matrix representing the graph
 * @param numVertices Number of vertices in the graph
 * @param numEdges Number of edges in the graph
 */
void Prim::TimeCounterMatrix(int **incMatrix, int numVertices, int numEdges) {
    cout << "Give number of iterations: ";
    int iterations;
    cin >> iterations;
    cout << endl;
    float wholeTime = 0;
    float avgTime;

    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        int mstWeight = AlgorithmCalculationFromMatrix(incMatrix, numVertices, numEdges);
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
 * @brief Runs Prim's algorithm on a graph represented as an adjacency list
 * @param adjList Adjacency list representing the graph
 * @param numVertices Number of vertices in the graph
 * @return Weight of the minimum spanning tree
 */
int Prim::AlgorithmCalculationFromList(slistEl **adjList, int numVertices) {
    int* key = new int[numVertices];
    int* parent = new int[numVertices];
    bool* inMST = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }
    key[0] = 0;
    int mstWeight = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, inMST, numVertices);
        inMST[u] = true;

        for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
            int v = p->v;
            if (!inMST[v] && p->weight < key[v]) {
                parent[v] = u;
                key[v] = p->weight;
            }
        }
    }

    mstWeight = 0;
    delete[] mst; // Clear previous MST
    mst = new Edge[numVertices - 1];
    mstSize = 0;
    for (int i = 1; i < numVertices; i++) {
        if (parent[i] != -1) {
            mst[mstSize++] = {parent[i], i, key[i]};
            mstWeight += key[i];
        }
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
    return mstWeight;
}


/**
 * @brief Measures and prints the time taken by Prim's algorithm on a graph represented as an adjacency list
 * @param adjList Adjacency list representing the graph
 * @param numVertices Number of vertices in the graph
 */
void Prim::TimeCounterList(slistEl **adjList, int numVertices) {
    cout << "Give number of iterations: ";
    int iterations;
    cin >> iterations;
    cout << endl;
    float wholeTime = 0;
    float avgTime;

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
