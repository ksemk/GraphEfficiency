// GraphsGenerating.cpp

#include "GraphsGenerating.h"
#include "SimulationOptions.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()

using namespace std;

int** GraphsGenerating::adjMatrix = nullptr;
int GraphsGenerating::numVertices = 0;
int GraphsGenerating::numEdges = 0;
slistEl** GraphsGenerating::adjList = nullptr;

const char* DIRECTORY_PATH = "C:\\Users\\10122\\CLionProjects\\GraphEfficiency\\resources\\"; // Ścieżka do katalogu z plikami grafów

void GraphsGenerating::loadGraphFromFile() {
    string fileName;
    string fullPath;

    cout << "Enter the file name to read data from: ";
    cin >> fileName;
    cout << endl;

    // Construct the full path to the file
    fullPath = DIRECTORY_PATH + fileName;
    FILE *inputFile = fopen(fullPath.c_str(), "r");

    // Check if the file exists
    if (!inputFile) {
        cout << "Cannot open the file" << endl;
        return;
    }

    // Read the number of edges and vertices
    fscanf(inputFile, "%d %d", &numEdges, &numVertices);

    // Allocate memory for the adjacency matrix
    adjMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjMatrix[i] = new int[numVertices];
    }

    // Initialize the adjacency matrix with zeros
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            adjMatrix[i][j] = 0;
        }
    }

    // Allocate memory for the adjacency list
    adjList = new slistEl*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjList[i] = nullptr;
    }

    int start, end, weight;
    while (fscanf(inputFile, "%d %d %d", &start, &end, &weight) != EOF) {
        adjMatrix[start][end] = weight; // Edge start->end with weight

        // Create a new adjacency list element
        slistEl *p = new slistEl;
        p->v = end;
        p->weight = weight;
        p->next = adjList[start];
        adjList[start] = p;
    }

    // Close the file
    fclose(inputFile);
}

void GraphsGenerating::printAdjacencyMatrix() {
    // Print adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    cout << "  ";
    for (int i = 0; i < numVertices; i++) cout << " " << i;
    cout << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << i << "  ";
        for (int j = 0; j < numVertices; j++) cout << (int) adjMatrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void GraphsGenerating::printAdjacencyList() {
    // Print adjacency list
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

void GraphsGenerating::generateRandomGraph(int vertices, int density) {
    freeMemory(); // Free existing graph memory, if any

    numVertices = vertices;
    numEdges = (density * (vertices * (vertices - 1)) / 2) / 100;

    // Allocate memory for the adjacency matrix
    adjMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            adjMatrix[i][j] = 0; // Initialize with zeros
        }
    }

    // Allocate memory for the adjacency list
    adjList = new slistEl*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjList[i] = nullptr;
    }

    srand(time(0)); // Seed for random number generation

    int edgesAdded = 0;
    while (edgesAdded < numEdges) {
        int start = rand() % numVertices;
        int end = rand() % numVertices;
        int weight = rand() % 9 + 1; // Random weight between 1 and 9

        if (start != end && adjMatrix[start][end] == 0) {
            adjMatrix[start][end] = weight; // Add edge to adjacency matrix

            // Add edge to adjacency list
            slistEl *p = new slistEl;
            p->v = end;
            p->weight = weight;
            p->next = adjList[start];
            adjList[start] = p;

            edgesAdded++;
        }
    }
}

void GraphsGenerating::freeMemory() {
    if (adjMatrix) {
        for (int i = 0; i < numVertices; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
        adjMatrix = nullptr;
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
