//
// Created by 10122 on 31.05.2024.
//

#include "GraphsGenerating.h"
#include "SimulationOptions.h"
#include <iostream>
#include <string>
#include <cstdio>


using namespace std;

int** GraphsGenerating::adjMatrix = nullptr;
int GraphsGenerating::numVertices = 0;
int GraphsGenerating::numEdges = 0;

const char* DIRECTORY_PATH = "C:\\Users\\10122\\CLionProjects\\GraphEfficiency\\resources\\"; // Ścieżka do katalogu z plikami grafów
// Typy dla dynamicznej tablicy list sąsiedztwa
struct slistEl {
    slistEl *next;
    int v;
};
slistEl **adjList; // Lista sąsiedztwa

void GraphsGenerating::loadGraphFromFile() {
    string fileName;
    string fullPath;

    cout << "Enter the file name to read data from: ";
    cin >> fileName;
    cout << endl;

    // Konstrukcja pełnej ścieżki do pliku
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
        adjMatrix[start][end] = weight; // Krawędź start->end obecna z wagą

        // Tworzenie nowego elementu listy sąsiedztwa
        slistEl *p = new slistEl;
        p->v = end;
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
            cout << " " << p->v;
            p = p->next;
        }
        cout << endl;
    }
}

void GraphsGenerating::freeMemory() {
    for (int i = 0; i < numVertices; ++i) {
        delete[] adjMatrix[i];
        slistEl *p = adjList[i];
        while (p) {
            slistEl *r = p;
            p = p->next;
            delete r;
        }
    }
    delete[] adjMatrix;
    delete[] adjList;
}

