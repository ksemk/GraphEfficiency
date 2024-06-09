#include "BellmanFord.h"
#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

/**
 * @brief This function implements the Bellman-Ford algorithm using adjacency matrix representation of the graph.
 * @param adjMatrix The adjacency matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 * @return A pair of arrays, where the first array contains the shortest distances from the start vertex to all other vertices,
 * and the second array contains the previous vertex in the shortest path from the start vertex to each vertex.
 */
pair<int *, int *> BellmanFord::AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int startVertex) {
    int *dist = new int[numVertices];
    int *prev = new int[numVertices];

    // Initialize distances and previous array
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX; // Set all distances to infinity
        prev[i] = -1; // No previous vertex
    }

    dist[startVertex] = 0; // Distance to the start vertex is 0

    // Relax edges |V| - 1 times
    for (int i = 1; i <= numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            for (int v = 0; v < numVertices; v++) {
                if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = u;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                printf("Graph contains a negative-weight cycle\n");
                delete[] dist;
                delete[] prev;
                return make_pair(nullptr, nullptr);
            }
        }
    }

    return make_pair(dist, prev);
}

/**
 * @brief This function implements the Bellman-Ford algorithm using adjacency list representation of the graph.
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 * @return A pair of arrays, where the first array contains the shortest distances from the start vertex to all other vertices,
 * and the second array contains the previous vertex in the shortest path from the start vertex to each vertex.
 */
pair<int *, int *> BellmanFord::AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int startVertex) {
    int *dist = new int[numVertices];
    int *prev = new int[numVertices];

    // Initialize distances and previous array
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX; // Set all distances to infinity
        prev[i] = -1; // No previous vertex
    }

    dist[startVertex] = 0; // Distance to the start vertex is 0

    // Relax edges |V| - 1 times
    for (int i = 1; i <= numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            for (slistEl *p = adjList[u]; p != nullptr; p = p->next) {
                int v = p->v;
                int weight = p->weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < numVertices; u++) {
        for (slistEl *p = adjList[u]; p != nullptr; p = p->next) {
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

/**
 * @brief This function prints the results of the Bellman-Ford algorithm.
 * It prints the shortest distance from the start vertex to each vertex, and the shortest path from the start vertex to each vertex.
 * @param dist The array of shortest distances from the start vertex to each vertex.
 * @param prev The array of previous vertices in the shortest path from the start vertex to each vertex.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 */
void BellmanFord::PrintResults(int *dist, int *prev, int numVertices, int startVertex) {
    // Print the results
    printf("Vertex\tDistance from Source\tPath\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d\t%d\t\t\t", i, dist[i]);
        if (dist[i] != INT_MAX) {
            int pathVertex = i;
            while (pathVertex != -1) {
                printf("%d", pathVertex);
                pathVertex = prev[pathVertex];
                if (pathVertex != -1) printf(" <- ");
            }
        }
        printf("\n");
    }
}

/**
 * @brief This function measures the time taken by the Bellman-Ford algorithm using adjacency matrix representation of the graph.
 * It runs the algorithm a specified number of times and prints the average time taken.
 * @param adjMatrix The adjacency matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 */
void BellmanFord::TimeCounterMatrix(int **adjMatrix, int numVertices, int startVertex) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        pair<int *, int *> results = AlgorithmCalculationFromMatrix(adjMatrix, numVertices, startVertex);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            PrintResults(results.first, results.second, numVertices, startVertex);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
        // Free allocated memory
        delete[] results.first;
        delete[] results.second;
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;

}

/**
 * @brief This function measures the time taken by the Bellman-Ford algorithm using adjacency list representation of the graph.
 * It runs the algorithm a specified number of times and prints the average time taken.
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 */
void BellmanFord::TimeCounterList(slistEl **adjList, int numVertices, int startVertex) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        pair<int *, int *> results = AlgorithmCalculationFromList(adjList, numVertices, startVertex);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            PrintResults(results.first, results.second, numVertices, startVertex);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
        // Free allocated memory
        delete[] results.first;
        delete[] results.second;
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}
