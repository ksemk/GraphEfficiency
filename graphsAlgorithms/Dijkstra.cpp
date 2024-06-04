//
// Created by 10122 on 01.06.2024.
//

#include "Dijkstra.h"
#include <iostream>
#include <climits>
#include <chrono>

using namespace std;

pair<int*, int*> Dijkstra::AlgorithmCalculationFromMatrix(int **adjMatrix, int numVertices, int startVertex) {
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

PriorityQueue::PriorityQueue(int capacity, int* dist) {
    this->capacity = capacity;
    this->size = 0;
    this->dist = dist;
    heap = new int[capacity];
    pos = new int[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
    delete[] pos;
}

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

void PriorityQueue::swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

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

bool PriorityQueue::isEmpty() {
    return size == 0;
}

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

    return make_pair(dist, prev);
}

void Dijkstra::PrintResults(int *dist, int *prev, int numVertices, int startVertex) {
    // Print the results
    cout << "Vertex\tDistance from Source\tPath" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << i << "\t" << dist[i] << "\t\t\t";
        if (dist[i] != INT_MAX) {
            int j = i;
            while (j != startVertex) {
                cout << j << " <- ";
                j = prev[j];
            }
            cout << startVertex << endl;
        } else {
            cout << "No path" << endl;
        }
    }

    delete[] dist;
    delete[] prev;
}

void Dijkstra::TimeCounterList(slistEl** adjList, int numVertices, int startVertex) {
    auto start = chrono::high_resolution_clock::now();
    pair<int*, int*> results = AlgorithmCalculationFromList(adjList, numVertices, startVertex);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> singleAlgorithmTime = end - start;
    PrintResults(results.first, results.second, numVertices, startVertex);
    cout << "Elapsed time: " << singleAlgorithmTime.count() / 1000 << " ms" << endl;
}


void Dijkstra::TimeCounterMatrix(int **adjMatrix, int numVertices, int startVertex) {
    auto start = chrono::high_resolution_clock::now();
    pair<int*, int*> results = AlgorithmCalculationFromMatrix(adjMatrix, numVertices, startVertex);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> singleAlgorithmTime = end - start;
    PrintResults(results.first, results.second, numVertices, startVertex);
    cout << "Elapsed time: " << singleAlgorithmTime.count() / 1000 << " ms" << endl;
}