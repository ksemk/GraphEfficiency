/**
 * @file GraphsGenerating.cpp
 * @brief This file contains the implementation of the GraphsGenerating class.
 */

#include "GraphsGenerating.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

// Initialize static members
int** GraphsGenerating::adjMatrix = nullptr;
int GraphsGenerating::numVertices = 0;
int GraphsGenerating::numEdges = 0;
slistEl** GraphsGenerating::adjList = nullptr;

// Define the directory path for the input files
const char* DIRECTORY_PATH = "C:\\Users\\10122\\CLionProjects\\GraphEfficiency\\resources\\";

/**
 * @brief Loads a graph from a file.
 *
 * This function reads a graph from a file and stores it in both adjacency matrix and adjacency list formats.
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

    adjMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjMatrix[i] = new int[numVertices]();
    }

    adjList = new slistEl*[numVertices]();

    int start, end, weight;
    while (fscanf(inputFile, "%d %d %d", &start, &end, &weight) != EOF) {
        adjMatrix[start][end] = weight;

        slistEl *p = new slistEl;
        p->v = end;
        p->weight = weight;
        p->next = adjList[start];
        adjList[start] = p;
    }

    fclose(inputFile);
}


/**
 * @brief Prints the adjacency matrix of the graph.
 *
 * This function prints the adjacency matrix representation of the graph to the console.
 */
void GraphsGenerating::printAdjacencyMatrix() {
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
 * @brief Generates a random graph.
 *
 * This function generates a random graph with a given number of vertices and density.
 * The density is a percentage that determines the number of edges in the graph.
 * The graph is stored in both adjacency matrix and adjacency list formats.
 *
 * @param vertices The number of vertices in the graph.
 * @param density The density of the graph, as a percentage.
 */
void GraphsGenerating::generateRandomGraph(int vertices, int density) {
    freeMemory();

    numVertices = vertices;
    numEdges = (density * (vertices * (vertices - 1)) / 2) / 100;

    adjMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjMatrix[i] = new int[numVertices]();
    }

    adjList = new slistEl*[numVertices]();

    srand(time(0));

    int edgesAdded = 0;
    while (edgesAdded < numEdges) {
        int start = rand() % numVertices;
        int end = rand() % numVertices;
        int weight = rand() % 9 + 1;

        if (start != end && adjMatrix[start][end] == 0) {
            adjMatrix[start][end] = weight;

            slistEl *p = new slistEl;
            p->v = end;
            p->weight = weight;
            p->next = adjList[start];
            adjList[start] = p;

            edgesAdded++;
        }
    }
}

/**
 * @brief Frees the memory used by the adjacency matrix and list.
 *
 * This function deletes the adjacency matrix and list and sets their pointers to nullptr.
 */
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