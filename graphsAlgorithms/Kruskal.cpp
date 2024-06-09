/**
 * @file Kruskal.cpp
 * @brief This file contains the implementation of the Kruskal class.
 */

#include "Kruskal.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// The resulting MST, stored as a vector of edges
vector<Kruskal::Edge> Kruskal::mst;


/**
 * @brief Finds the set of an element i (uses path compression technique).
 *
 * @param parent The parent array.
 * @param i The element.
 * @return The set of the element.
 */
int Kruskal::find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]);
}

/**
 * @brief Unions two sets of x and y (uses union by rank).
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
 * @brief Sorts the edges of the graph in non-decreasing order of their weight.
 *
 * @param edges The edges of the graph.
 */
void Kruskal::sortEdges(vector<Edge>& edges) {
    for (size_t i = 0; i < edges.size() - 1; i++) {
        for (size_t j = 0; j < edges.size() - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                swap(edges[j], edges[j + 1]);
            }
        }
    }
}

/**
 * @brief Runs Kruskal's algorithm on a graph represented as an adjacency matrix.
 *
 * @param adjMatrix The adjacency matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 * @return The total weight of the MST.
 */
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

/**
 * @brief Runs Kruskal's algorithm on a graph represented as an adjacency list.
 *
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 * @return The total weight of the MST.
 */
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

/**
 * @brief Prints the results of Kruskal's algorithm.
 *
 * @param mstWeight The total weight of the MST.
 * @param elapsed The time taken by the algorithm, in seconds.
 */
void Kruskal::PrintResults(int mstWeight, double elapsed) {
    printf("Minimum Spanning Tree Weight: %d\n", mstWeight);
    printf("%-10s %-10s\n", "Edge", "Weight");
    for (const auto& edge : mst)
        printf("%-4d - %-4d \t%-4d\n", edge.src, edge.dest, edge.weight);
    printf("Elapsed time: %.3f ms\n", elapsed);
}

/**
 * @brief Measures and prints the time taken by Kruskal's algorithm on a graph represented as an adjacency matrix.
 *
 * @param adjMatrix The adjacency matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 */
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

/**
 * @brief Measures and prints the time taken by Kruskal's algorithm on a graph represented as an adjacency list.
 *
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 */
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
