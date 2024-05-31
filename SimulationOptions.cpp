//
// Created by 10122 on 29.05.2024.
//

#include "SimulationOptions.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;
int menuchoice;
char **adjMatrix; // Macierz sąsiedztwa
int numVertices; // Liczba wierzchołków
int numEdges; // Liczba krawędzi

// Typy dla dynamicznej tablicy list sąsiedztwa
struct slistEl {
    slistEl *next;
    int v;
};
slistEl **adjList; // Lista sąsiedztwa
const char* DIRECTORY_PATH = "C:\\Users\\10122\\CLionProjects\\GraphEfficiency\\resources\\"; // Ścieżka do katalogu z plikami grafów

void SimulationOptions::runMenu() {
    do {
        cout << "|---------------------------------------------------|" << endl;
        cout << "|                     MAIN MENU                     |" << endl;
        cout << "|---------------------------------------------------|" << endl;
        cout << "| 1 - Compute the Minimum Spanning Tree (MST)       |" << endl;
        cout << "| 2 - Compute the shortest paths                    |" << endl;
        cout << "| 3 - Compute the the maximum flow                  |" << endl;
        cout << "|---------------------------------------------------|" << endl;
        cout << "| 0 - Exit the program                              |" << endl;
        cout << "|---------------------------------------------------|" << endl;
        cout << "Enter your choice: ";
        cin >> menuchoice;
        cout << endl;
        switch (menuchoice) {
            case 1:
                do {
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "|       CHOOSE THE ALGORITHM FOR MST COMPUTING      |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 1 - Prim's algorithm                              |" << endl;
                    cout << "| 2 - Kruskal's algorithm                           |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 0 - Back to the main menu                         |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "Enter your choice: ";
                    cin >> menuchoice;
                    cout << endl;
                    switch (menuchoice) {
                        case 1:
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "|      CHOOSE THE OPTION FOR PRIM'S ALGORITHM       |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        loadGraphFromFile();
                                        break;
                                    case 2:
                                        cout << "Generating random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        printAdjacencyMatrix();
                                        printAdjacencyList();
                                        break;
                                    case 0:
                                        cout << "Back to the main menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (menuchoice != 0);
                            break;
                        case 2:
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "|     CHOOSE THE OPTION FOR KRUSKAL'S ALGORITHM     |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        loadGraphFromFile();
                                        break;
                                    case 2:
                                        cout << "Generating random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        printAdjacencyMatrix();
                                        printAdjacencyList();
                                        break;
                                    case 0:
                                        cout << "Back to the main menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (menuchoice != 0);
                            break;
                        case 0:
                            cout << "Back to the main menu" << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (menuchoice != 0);
                break;
            case 2:
                do {
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| CHOOSE THE ALGORITHM FOR SHORTEST PATH COMPUTING  |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 1 - Dijkstra's algorithm                          |" << endl;
                    cout << "| 2 - Bellman-Ford algorithm                        |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 0 - Back to the main menu                         |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "Enter your choice: ";
                    cin >> menuchoice;
                    cout << endl;
                    switch (menuchoice) {
                        case 1:
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "|      CHOOSE THE OPTION FOR DIJKSTRA'S ALGORITHM   |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        break;
                                    case 2:
                                        cout << "Generate random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        printAdjacencyMatrix();
                                        printAdjacencyList();
                                        break;
                                    case 0:
                                        cout << "Back to the main menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (menuchoice != 0);
                            break;
                        case 2:
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "|    CHOOSE THE OPTION FOR BELLMAN-FORD ALGORITHM   |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        break;
                                    case 2:
                                        cout << "Generate random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        printAdjacencyMatrix();
                                        printAdjacencyList();
                                        break;
                                    case 0:
                                        cout << "Back to the main menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (menuchoice != 0);
                            break;
                        case 0:
                            cout << "Back to the main menu" << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (menuchoice != 0);
                break;
            case 3:
                do {
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "|    CHOOSE THE OPTIONS MAXIMUM FLOW ALGORITHM      |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 1 - Load graph from file                          |" << endl;
                    cout << "| 2 - Generate random graph                         |" << endl;
                    cout << "| 3 - Print existed graph                           |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 0 - Back to the main menu                         |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "Enter your choice: ";
                    cin >> menuchoice;
                    cout << endl;
                    switch (menuchoice) {
                        case 1:
                            cout << "Load graph from file" << endl;
                            break;
                        case 2:
                            cout << "Generate random graph" << endl;
                            break;
                        case 3:
                            cout << "Print existed graph" << endl;
                            break;
                        case 0:
                            cout << "Back to the main menu" << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (menuchoice != 0);
                break;
            case 0:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (menuchoice != 0);
}


void SimulationOptions::loadGraphFromFile() {
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
    adjMatrix = new char*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjMatrix[i] = new char[numVertices];
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

void SimulationOptions::printAdjacencyMatrix() {
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

void SimulationOptions::printAdjacencyList() {
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
