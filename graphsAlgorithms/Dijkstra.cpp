#include "Dijkstra.h"
#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

/**
 * @brief This function implements Dijkstra's algorithm using adjacency matrix representation of the graph.
 * @param adjMatrix The adjacency matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 * @return A pair of arrays, where the first array contains the shortest distances from the start vertex to all other vertices,
 * and the second array contains the previous vertex in the shortest path from the start vertex to each vertex.
 */
pair<int *, int *> Dijkstra::AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int startVertex) {
    int *dist = new int[numVertices]; // Array to store shortest distance from startVertex
    bool *visited = new bool[numVertices]; // Array to mark visited vertices
    int *prev = new int[numVertices]; // Array to store the previous vertex in the path

    // Initialize distances and visited array
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX; // Set all distances to infinity
        visited[i] = false; // Mark all vertices as unvisited
        prev[i] = -1; // No previous vertex
    }

    dist[startVertex] = 0; // Distance to the start vertex is 0

    for (int i = 0; i < numVertices - 1; i++) {
        // Find the vertex with the minimum distance that hasn't been visited yet
        int minDist = INT_MAX, u = -1;
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        // Mark the chosen vertex as visited
        visited[u] = true;

        // Update the distances to the neighboring vertices
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }

    delete[] visited;

    return make_pair(dist, prev);
}

/**
 * @brief PriorityQueue is a helper class used in Dijkstra's algorithm.
 * It is a min-heap data structure where the key of each node is the shortest distance from the start vertex to the node.
 * @param capacity The maximum number of elements that the PriorityQueue can hold.
 * @param dist The array of distances from the start vertex to each vertex.
 */
PriorityQueue::PriorityQueue(int capacity, int *dist) {
    this->capacity = capacity;
    this->size = 0;
    this->dist = dist;
    heap = new int[capacity];
    pos = new int[capacity];
}

/**
 * @brief Destructor for the PriorityQueue class.
 * It frees the memory allocated for the heap and positions arrays.
 */
PriorityQueue::~PriorityQueue() {
    delete[] heap;
    delete[] pos;
}

/**
 * @brief This function maintains the heap property of the PriorityQueue.
 * @param idx The index of the node to heapify.
 */
void PriorityQueue::heapify(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && dist[heap[left]] < dist[heap[smallest]])
        smallest = left;

    if (right < size && dist[heap[right]] < dist[heap[smallest]])
        smallest = right;

    if (smallest != idx) {
        swap(&heap[smallest], &heap[idx]);
        swap(&pos[heap[smallest]], &pos[heap[idx]]);
        heapify(smallest);
    }
}

/**
 * @brief This function swaps two integers.
 * @param a The first integer to swap.
 * @param b The second integer to swap.
 */
void PriorityQueue::swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief This function inserts a new node into the PriorityQueue.
 * @param v The vertex to insert.
 */
void PriorityQueue::push(int v) {
    size++;
    int i = size - 1;
    heap[i] = v;
    pos[v] = i;

    while (i && dist[heap[i]] < dist[heap[(i - 1) / 2]]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        swap(&pos[heap[i]], &pos[heap[(i - 1) / 2]]);
        i = (i - 1) / 2;
    }
}

/**
 * @brief This function removes and returns the root of the PriorityQueue.
 * @return The root of the PriorityQueue, or -1 if the PriorityQueue is empty.
 */
int PriorityQueue::pop() {
    if (size == 0)
        return -1;

    int root = heap[0];

    if (size > 1) {
        heap[0] = heap[size - 1];
        pos[heap[0]] = 0;
        heapify(0);
    }

    size--;
    return root;
}

/**
 * @brief This function checks if the PriorityQueue is empty.
 * @return True if the PriorityQueue is empty, false otherwise.
 */
bool PriorityQueue::isEmpty() {
    return size == 0;
}
/**
 * @brief This function implements Dijkstra's algorithm using adjacency list representation of the graph.
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 * @return A pair of arrays, where the first array contains the shortest distances from the start vertex to all other vertices,
 * and the second array contains the previous vertex in the shortest path from the start vertex to each vertex.
 */
pair<int *, int *> Dijkstra::AlgorithmCalculationFromList(slistEl **adjList, int numVertices, int startVertex) {
    int *dist = new int[numVertices];
    int *prev = new int[numVertices];
    bool *visited = new bool[numVertices];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }

    dist[startVertex] = 0;
    PriorityQueue pq(numVertices, dist);
    pq.push(startVertex);

    while (!pq.isEmpty()) {
        int u = pq.pop();
        visited[u] = true;

        for (slistEl *p = adjList[u]; p != nullptr; p = p->next) {
            int v = p->v;
            int weight = p->weight;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(v);
            }
        }
    }

    return make_pair(dist, prev);
}

/**
 * @brief This function prints the results of Dijkstra's algorithm.
 * It prints the shortest distance from the start vertex to each vertex, and the shortest path from the start vertex to each vertex.
 * @param dist The array of shortest distances from the start vertex to each vertex.
 * @param prev The array of previous vertices in the shortest path from the start vertex to each vertex.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 */
void Dijkstra::PrintResults(int *dist, int *prev, int numVertices, int startVertex) {
    // Print the results
    printf("%-10s%-25s%s\n", "Vertex", "Distance from Source", "Path");
    for (int i = 0; i < numVertices; i++) {
        printf("%-10d%-25d", i, dist[i]);
        if (dist[i] != INT_MAX) {
            int j = i;
            while (j != startVertex) {
                printf("%d <- ", j);
                j = prev[j];
            }
            printf("%d\n", startVertex);
        } else {
            printf("No path\n");
        }
    }
}

/**
 * @brief This function measures the time taken by Dijkstra's algorithm using adjacency list representation of the graph.
 * It runs the algorithm a specified number of times and prints the average time taken.
 * @param adjList The adjacency list representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 */
void Dijkstra::TimeCounterList(slistEl **adjList, int numVertices, int startVertex) {
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

/**
 * @brief This function measures the time taken by Dijkstra's algorithm using adjacency matrix representation of the graph.
 * It runs the algorithm a specified number of times and prints the average time taken.
 * @param adjMatrix The adjacency matrix representation of the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 */
void Dijkstra::TimeCounterMatrix(int **adjMatrix, int numVertices, int startVertex) {
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
