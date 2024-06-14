#include "GraphsGenerating.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

// Initialize static members
int** GraphsGenerating::incMatrix = nullptr;
int GraphsGenerating::numVertices = 0;
int GraphsGenerating::numEdges = 0;
slistEl** GraphsGenerating::adjList = nullptr;

// Define the directory path for the input files
const char* DIRECTORY_PATH = "C:\\Users\\10122\\CLionProjects\\GraphEfficiency\\resources\\";

/**
 * @brief Loads a graph from a file.
 *
 * This function reads a graph from a file and stores it in both incidence matrix and adjacency list formats.
 * The file should contain the number of edges and vertices on the first line, followed by lines containing the start vertex, end vertex, and weight of each edge.
 */
void GraphsGenerating::loadGraphFromFile() {
    string fileName;
    cin >> fileName;
    string fullPath = DIRECTORY_PATH + fileName;
    FILE *inputFile = fopen(fullPath.c_str(), "r");

    if (!inputFile) {
        cout << "Cannot open the file" << endl;
        return;
    }

    fscanf(inputFile, "%d %d", &numEdges, &numVertices);

    incMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        incMatrix[i] = new int[numEdges]();
    }

    adjList = new slistEl*[numVertices]();

    int start, end, weight, edgeIdx = 0;
    while (fscanf(inputFile, "%d %d %d", &start, &end, &weight) != EOF) {
        incMatrix[start][edgeIdx] = weight;
        incMatrix[end][edgeIdx] = -weight;

        slistEl *p = new slistEl;
        p->v = end;
        p->weight = weight;
        p->next = adjList[start];
        adjList[start] = p;

        edgeIdx++;
    }

    fclose(inputFile);
}

/**
 * @brief Prints the incidence matrix of the graph.
 *
 * This function prints the incidence matrix representation of the graph to the console.
 */
void GraphsGenerating::printIncidenceMatrix() {
    cout << "Incidence Matrix:" << endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numEdges; j++) {
            cout << incMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * @brief Prints the adjacency list of the graph.
 *
 * This function prints the adjacency list representation of the graph to the console.
 */
void GraphsGenerating::printAdjacencyList() {
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << "A [" << i << "] =";
        slistEl *p = adjList[i];
        while (p) {
            cout << " " << p->v << " (weight: " << p->weight << ");";
            p = p->next;
        }
        cout << endl;
    }
}

/**
 * @brief Adds an edge to the incidence matrix and adjacency list.
 *
 * @param start The start vertex of the edge.
 * @param end The end vertex of the edge.
 * @param weight The weight of the edge.
 * @param edgeIndex The index of the edge in the incidence matrix.
 */
void addEdge(int start, int end, int weight, int edgeIndex, int** incMatrix, slistEl** adjList) {
    incMatrix[start][edgeIndex] = weight;
    incMatrix[end][edgeIndex] = -weight;

    slistEl *p = new slistEl;
    p->v = end;
    p->weight = weight;
    p->next = adjList[start];
    adjList[start] = p;

    slistEl *pReverse = new slistEl;
    pReverse->v = start;
    pReverse->weight = weight;
    pReverse->next = adjList[end];
    adjList[end] = pReverse;
}

/**
 * @brief Generates a random graph.
 *
 * This function generates a random graph with a given number of vertices and density.
 * The density is a percentage that determines the number of edges in the graph.
 * The graph is stored in both incidence matrix and adjacency list formats.
 *
 * @param vertices The number of vertices in the graph.
 * @param density The density of the graph, as a percentage.
 */
void GraphsGenerating::generateRandomGraph(int vertices, int density) {
    freeMemory();

    numVertices = vertices;
    numEdges = (density * (vertices * (vertices - 1)) / 2) / 100;

    incMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        incMatrix[i] = new int[numEdges]();
    }

    adjList = new slistEl*[numVertices]();

    srand(time(0));

    // Create a spanning tree to ensure the graph is connected
    int* verticesList = new int[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        verticesList[i] = i;
    }

    // Shuffle the vertices list to create a random spanning tree
    for (int i = numVertices - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(verticesList[i], verticesList[j]);
    }

    int edgesAdded = 0;
    for (int i = 1; i < numVertices; ++i) {
        int start = verticesList[i - 1];
        int end = verticesList[i];
        int weight = rand() % 50 + 1;
        addEdge(start, end, weight, edgesAdded++, incMatrix, adjList);
    }

    // Add additional edges to meet the required density
    while (edgesAdded < numEdges) {
        int start = rand() % numVertices;
        int end = rand() % numVertices;
        if (start != end) {
            bool alreadyConnected = false;
            for (int i = 0; i < edgesAdded; ++i) {
                if ((incMatrix[start][i] != 0 && incMatrix[end][i] != 0) ||
                    (incMatrix[end][i] != 0 && incMatrix[start][i] != 0)) {
                    alreadyConnected = true;
                    break;
                }
            }
            if (!alreadyConnected) {
                int weight = rand() % 9 + 1;
                addEdge(start, end, weight, edgesAdded++, incMatrix, adjList);
            }
        }
    }

    delete[] verticesList;
}

/**
 * @brief Frees the memory used by the incidence matrix and list.
 *
 * This function deletes the incidence matrix and list and sets their pointers to nullptr.
 */
void GraphsGenerating::freeMemory() {
    if (incMatrix) {
        for (int i = 0; i < numVertices; ++i) {
            delete[] incMatrix[i];
        }
        delete[] incMatrix;
        incMatrix = nullptr;
    }

    if (adjList) {
        for (int i = 0; i < numVertices; ++i) {
            slistEl *p = adjList[i];
            while (p) {
                slistEl *r = p;
                p = p->next;
                delete r;
            }
        }
        delete[] adjList;
        adjList = nullptr;
    }
}
