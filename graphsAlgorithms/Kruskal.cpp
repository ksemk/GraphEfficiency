/**
 * @file Kruskal.cpp
 * @brief This file contains the implementation of the Kruskal class.
 */

#include "Kruskal.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>

using namespace std;

// The resulting MST, stored as an array of edges
Kruskal::Edge* Kruskal::mst = nullptr;
int Kruskal::mstSize = 0;

/**
 * @brief Finds the set of an element i (uses path compression technique).
 *
 * @param parent The parent array.
 * @param i The element.
 * @return The set of the element.
 */
int Kruskal::find(int parent[], int i) {
    while (parent[i] != i) {
        parent[i] = parent[parent[i]]; // Path compression
        i = parent[i];
    }
    return i;
}

/**
 * @brief Unions two sets of x and y.
 *
 * @param parent The parent array.
 * @param rank The rank array.
 * @param x The first set.
 * @param y The second set.
 */
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

/**
 * @brief Merges two subarrays of edges.
 *
 * @param edges The array of edges.
 * @param left The left index.
 * @param mid The middle index.
 * @param right The right index.
 */
void merge(Kruskal::Edge edges[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Kruskal::Edge* L = new Kruskal::Edge[n1];
    Kruskal::Edge* R = new Kruskal::Edge[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = edges[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = edges[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].weight <= R[j].weight) {
            edges[k] = L[i];
            i++;
        } else {
            edges[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        edges[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        edges[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

/**
 * @brief Sorts edges using merge sort.
 *
 * @param edges The array of edges.
 * @param left The left index.
 * @param right The right index.
 */
void mergeSort(Kruskal::Edge edges[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(edges, left, mid);
    mergeSort(edges, mid + 1, right);
    merge(edges, left, mid, right);
}

/**
 * @brief Runs Kruskal's algorithm on a graph represented as an incidence matrix.
 *
 * @param incMatrix The incidence matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 * @return The total weight of the MST.
 */
int Kruskal::AlgorithmCalculationFromMatrix(int **incMatrix, int numVertices, int numEdges) {
    Edge* edges = new Edge[numEdges];
    int edgeCount = 0;

    for (int e = 0; e < numEdges; ++e) {
        int u = -1, v = -1, weight = 0;
        for (int i = 0; i < numVertices; ++i) {
            if (incMatrix[i][e] != 0) {
                if (u == -1) {
                    u = i;
                    weight = abs(incMatrix[i][e]);
                } else {
                    v = i;
                    break;
                }
            }
        }
        if (u != -1 && v != -1) {
            edges[edgeCount++] = {u, v, weight};
        }
    }

    mergeSort(edges, 0, edgeCount - 1);

    int *parent = new int[numVertices];
    int *rank = new int[numVertices];

    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mstWeight = 0;
    if (mst != nullptr) {
        delete[] mst;
    }
    mst = new Edge[edgeCount];
    mstSize = 0;

    for (int i = 0; i < edgeCount; ++i) {
        int x = find(parent, edges[i].src);
        int y = find(parent, edges[i].dest);

        if (x != y) {
            mstWeight += edges[i].weight;
            Union(parent, rank, x, y);
            mst[mstSize++] = edges[i];
        }
    }

    delete[] edges;
    delete[] parent;
    delete[] rank;

    return mstWeight;
}

/**
 * @brief Runs Kruskal's algorithm on a graph represented as an adjacency list.
 *
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @return The total weight of the MST.
 */
int Kruskal::AlgorithmCalculationFromList(slistEl **adjList, int numVertices) {
    int numEdges = 0;
    for (int u = 0; u < numVertices; ++u) {
        for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
            if (u < p->v) {
                numEdges++;
            }
        }
    }

    Edge* edges = new Edge[numEdges];
    int edgeCount = 0;
    for (int u = 0; u < numVertices; ++u) {
        for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
            if (u < p->v) {
                edges[edgeCount++] = {u, p->v, p->weight};
            }
        }
    }

    mergeSort(edges, 0, edgeCount - 1);

    int *parent = new int[numVertices];
    int *rank = new int[numVertices];

    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mstWeight = 0;
    if (mst != nullptr) {
        delete[] mst;
    }
    mst = new Edge[edgeCount];
    mstSize = 0;

    for (int i = 0; i < edgeCount; ++i) {
        int x = find(parent, edges[i].src);
        int y = find(parent, edges[i].dest);

        if (x != y) {
            mstWeight += edges[i].weight;
            Union(parent, rank, x, y);
            mst[mstSize++] = edges[i];
        }
    }

    delete[] edges;
    delete[] parent;
    delete[] rank;

    return mstWeight;
}

/**
 * @brief Prints the results of Kruskal's algorithm.
 *
 * @param mstWeight The total weight of the MST.
 * @param elapsed The time taken by the algorithm, in seconds.
 */
void Kruskal::PrintResults(int mstWeight, double elapsed) {
    printf("Minimum Spanning Tree Weight: %d\n", mstWeight);
    printf("%-10s %-10s\n", "Edge", "Weight");
    for (int i = 0; i < mstSize; ++i) {
        printf("%-4d - %-4d \t%-4d\n", mst[i].src, mst[i].dest, mst[i].weight);
    }
    printf("Elapsed time: %.3f ms\n", elapsed);
}

/**
 * @brief Measures and prints the time taken by Kruskal's algorithm on a graph represented as an incidence matrix.
 *
 * @param incMatrix The incidence matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 */
void Kruskal::TimeCounterMatrix(int **incMatrix, int numVertices, int numEdges) {
    printf("Give number of iterations: ");
    int iterations;
    float wholeTime = 0;
    float avgTime;
    scanf("%d", &iterations);
    printf("\n");
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
 * @brief Measures and prints the time taken by Kruskal's algorithm on a graph represented as an adjacency list.
 *
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 */
void Kruskal::TimeCounterList(slistEl **adjList, int numVertices) {
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
