//
// Created by 10122 on 29.05.2024.
//

#include "GraphsAlgorithms.h"
#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

struct Edge {
    int src, dest, weight;
};

int findSet(int i, int parent[]) {
    if (i == parent[i])
        return i;
    else
        return findSet(parent[i], parent);
}

void unionSets(int u, int v, int parent[], int rank[]) {
    int rootU = findSet(u, parent);
    int rootV = findSet(v, parent);

    if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

void GraphsAlgorithms::PrimsAlgorithm(int **adjMatrix, int numVertices) {
    int *parent = new int[numVertices];
    int *key = new int[numVertices];
    bool *inMST = new bool[numVertices];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numVertices - 1; count++) {
        int min = INT_MAX, u = -1;

        for (int v = 0; v < numVertices; v++)
            if (!inMST[v] && key[v] < min)
                min = key[v], u = v;

        inMST[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = adjMatrix[u][v];
            }
        }
    }

    // Print the constructed MST
    cout << "Edge \tWeight\n";
    for (int i = 1; i < numVertices; i++) {
        cout << parent[i] << " - " << i << " \t" << adjMatrix[parent[i]][i] << " \n";
    }

    delete[] parent;
    delete[] key;
    delete[] inMST;
}


void GraphsAlgorithms::KruskalsAlgorithm(int **adjMatrix, int numVertices) {
    Edge *edges = new Edge[numVertices * numVertices];
    int edgeCount = 0;

    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (adjMatrix[i][j]) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = adjMatrix[i][j];
                edgeCount++;
            }
        }
    }

    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    int *parent = new int[numVertices];
    int *rank = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    Edge *mst = new Edge[numVertices];
    int mstCount = 0;

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int uSet = findSet(u, parent);
        int vSet = findSet(v, parent);

        if (uSet != vSet) {
            mst[mstCount++] = edges[i];
            unionSets(uSet, vSet, parent, rank);
        }
    }

    cout << "Edge \tWeight\n";
    for (int i = 0; i < mstCount; i++)
        cout << mst[i].src << " - " << mst[i].dest << " \t" << mst[i].weight << " \n";

    delete[] edges;
    delete[] parent;
    delete[] rank;
    delete[] mst;
}

void GraphsAlgorithms::DijkstrasAlgorithm(int **adjMatrix, int numVertices, int startVertex) {
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

    // Free allocated memory
    delete[] dist;
    delete[] visited;
    delete[] prev;
}

void GraphsAlgorithms::BellmanFordAlgorithm(int **adjMatrix, int numVertices, int startVertex) {
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
                return;
            }
        }
    }

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

    // Free allocated memory
    delete[] dist;
    delete[] prev;
}

// Funkcja pomocnicza BFS
bool bfs(int **rGraph, int s, int t, int parent[], int numVertices) {
    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    int *queue = new int[numVertices];
    int front = 0, back = 0;
    queue[back++] = s;
    visited[s] = true;
    parent[s] = -1;

    while (front != back) {
        int u = queue[front++];
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    delete[] visited;
                    delete[] queue;
                    return true;
                }
                queue[back++] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    delete[] visited;
    delete[] queue;
    return false;
}

void GraphsAlgorithms::FordFulkersonAlgorithmBFS(int **adjMatrix, int numVertices, int startVertex, int endVertex) {
    int **rGraph = new int *[numVertices];
    for (int i = 0; i < numVertices; i++) {
        rGraph[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            rGraph[i][j] = adjMatrix[i][j];
        }
    }

    int *parent = new int[numVertices];
    int maxFlow = 0;

    while (bfs(rGraph, startVertex, endVertex, parent, numVertices)) {
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    cout << "Max flow: " << maxFlow << endl;

    for (int i = 0; i < numVertices; i++)
        delete[] rGraph[i];
    delete[] rGraph;
    delete[] parent;
}

// Funkcja pomocnicza DFS
bool dfs(int **rGraph, int s, int t, int parent[], int numVertices) {
    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    int *stack = new int[numVertices];
    int top = -1;
    stack[++top] = s;
    visited[s] = true;
    parent[s] = -1;

    while (top != -1) {
        int u = stack[top--];
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    delete[] visited;
                    delete[] stack;
                    return true;
                }
                stack[++top] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    delete[] visited;
    delete[] stack;
    return false;
}

void GraphsAlgorithms::FordFulkersonAlgorithmDFS(int **adjMatrix, int numVertices, int startVertex, int endVertex) {
    int **rGraph = new int *[numVertices];
    for (int i = 0; i < numVertices; i++) {
        rGraph[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            rGraph[i][j] = adjMatrix[i][j];
        }
    }

    int *parent = new int[numVertices];
    int maxFlow = 0;

    while (dfs(rGraph, startVertex, endVertex, parent, numVertices)) {
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    cout << "Max flow using DFS: " << maxFlow << endl;

    for (int i = 0; i < numVertices; i++)
        delete[] rGraph[i];
    delete[] rGraph;
    delete[] parent;
}

