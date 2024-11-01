#include "Dijkstra.h"
#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

/**
 * @brief Executes Dijkstra's algorithm on a graph represented as an incidence matrix.
 * @param incMatrix The incidence matrix representing the graph.
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 * @param startVertex The starting vertex for the algorithm.
 * @return A pair of arrays representing the shortest distances and the previous vertices.
 */
pair<int*, int*> Dijkstra::AlgorithmCalculationFromMatrix(int** incMatrix, int numVertices, int numEdges, int startVertex) {
    int* dist = new int[numVertices];
    bool* visited = new bool[numVertices];
    int* prev = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        prev[i] = -1;
    }

    dist[startVertex] = 0;
    PriorityQueue pq(numVertices, dist);
    pq.push(startVertex);

    while (!pq.isEmpty()) {
        int u = pq.pop();
        visited[u] = true;

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
                if (v != -1 && !visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push(v);
                }
            }
        }
    }

    delete[] visited;

    return make_pair(dist, prev);
}

/**
 * @brief Constructor for the PriorityQueue class.
 * @param capacity The maximum capacity of the priority queue.
 * @param dist The array of distances from the source vertex.
 */
PriorityQueue::PriorityQueue(int capacity, int* dist) {
    this->capacity = capacity;
    this->size = 0;
    this->dist = dist;
    heap = new int[capacity];
    pos = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        pos[i] = -1; // Initialize positions as -1 (not in the heap)
    }
}

/**
 * @brief Destructor for the PriorityQueue class.
 */
PriorityQueue::~PriorityQueue() {
    delete[] heap;
    delete[] pos;
}

/**
 * @brief Heapify function for maintaining the heap property of the priority queue.
 * @param idx The index of the element to be heapified.
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
 * @brief Swap function for swapping two elements in the priority queue.
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 */
void PriorityQueue::swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Inserts a vertex into the priority queue.
 * @param v The vertex to be inserted.
 */
void PriorityQueue::push(int v) {
    if (pos[v] != -1) { // Vertex is already in the heap, decrease its key
        decreaseKey(v);
    } else { // Vertex is not in the heap, insert it
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
}

/**
 * @brief Decreases the key (distance) of a vertex.
 * @param v The vertex whose key is to be decreased.
 */
void PriorityQueue::decreaseKey(int v) {
    int i = pos[v];
    while (i && dist[heap[i]] < dist[heap[(i - 1) / 2]]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        swap(&pos[heap[i]], &pos[heap[(i - 1) / 2]]);
        i = (i - 1) / 2;
    }
}

/**
 * @brief Removes and returns the vertex with the highest priority (lowest distance).
 * @return The vertex with the highest priority.
 */
int PriorityQueue::pop() {
    if (size == 0)
        return -1;

    int root = heap[0];

    if (size > 1) {
        heap[0] = heap[size - 1];
        pos[heap[0]] = 0;
        pos[root] = -1; // Mark the removed element as not in the heap
        heapify(0);
    } else {
        pos[root] = -1; // Mark the removed element as not in the heap
    }

    size--;
    return root;
}

/**
 * @brief Checks if the priority queue is empty.
 * @return True if the priority queue is empty, false otherwise.
 */
bool PriorityQueue::isEmpty() {
    return size == 0;
}

/**
 * @brief Executes Dijkstra's algorithm on a graph represented as an adjacency list.
 * @param adjList The adjacency list representing the graph.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 * @return A pair of arrays representing the shortest distances and the previous vertices.
 */
pair<int*, int*> Dijkstra::AlgorithmCalculationFromList(slistEl** adjList, int numVertices, int startVertex) {
    int* dist = new int[numVertices];
    int* prev = new int[numVertices];
    bool* visited = new bool[numVertices];

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

        for (slistEl* p = adjList[u]; p != nullptr; p = p->next) {
            int v = p->v;
            int weight = p->weight;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(v);
            }
        }
    }

    delete[] visited;

    return make_pair(dist, prev);
}

/**
 * @brief Prints the results of Dijkstra's algorithm.
 * @param dist The array of shortest distances.
 * @param prev The array of previous vertices.
 * @param numVertices The number of vertices in the graph.
 * @param startVertex The starting vertex for the algorithm.
 */
void Dijkstra::PrintResults(int* dist, int* prev, int numVertices, int startVertex) {
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
 * @brief Measures and prints the time taken by Dijkstra's algorithm on a graph represented as an adjacency list.
 * @param adjList The adjacency list representing the graph.
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
        delete[] results.first;
        delete[] results.second;
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}

/**
 * @brief Measures and prints the time taken by Dijkstra's algorithm on a graph represented as an incidence matrix.
 * @param incMatrix The incidence matrix representing the graph.
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 * @param startVertex The starting vertex for the algorithm.
 */
void Dijkstra::TimeCounterMatrix(int **incMatrix, int numVertices, int numEdges, int startVertex) {
    cout << "Give number of iterations: ";
    int iterations;
    float wholeTime = 0;
    float avgTime;
    cin >> iterations;
    cout << endl;
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        pair<int *, int *> results = AlgorithmCalculationFromMatrix(incMatrix, numVertices, numEdges, startVertex);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        if (iterations == 1) {
            PrintResults(results.first, results.second, numVertices, startVertex);
        }
        cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << endl;
        wholeTime += elapsed.count();
        delete[] results.first;
        delete[] results.second;
    }
    avgTime = wholeTime / iterations * 1000;
    cout << "Average time: " << avgTime << " ms" << endl;
}
