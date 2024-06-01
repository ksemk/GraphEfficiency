//
// Created by 10122 on 29.05.2024.
//

#include "SimulationOptions.h"
#include "GraphsGenerating.h"
#include "GraphsAlgorithms.h"
#include <iostream>

using namespace std;
int menuchoice;

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
                                cout << "| 4 - Run the algorithm                             |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        cout << "Generating random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Prim's algorithm for computing minimal spanning tree" << endl;
                                        GraphsAlgorithms::PrimsAlgorithm(GraphsGenerating::adjMatrix,
                                                                         GraphsGenerating::numVertices);
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
                                cout << "| 4 - Run the algorithm                             |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        cout << "Generating random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Kruskal's algorithm for computing minimal spanning tree" << endl;
                                        GraphsAlgorithms::KruskalsAlgorithm(GraphsGenerating::adjMatrix,
                                                                            GraphsGenerating::numVertices);
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
                                cout << "| 4 - Run the algorithm                             |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        cout << "Generate random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Dijkstra's algorithm for computing shortest path" << endl;
                                        GraphsAlgorithms::DijkstrasAlgorithm(GraphsGenerating::adjMatrix,
                                                                             GraphsGenerating::numVertices, 0);
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
                                cout << "| 4 - Run the algorithm                             |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        cout << "Generate random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Bellman-Ford algorithm for computing shortest path" << endl;
                                        GraphsAlgorithms::BellmanFordAlgorithm(GraphsGenerating::adjMatrix,
                                                                               GraphsGenerating::numVertices, 0);
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
                    cout << "|       CHOOSE THE ALGORITHM FOR MAXIMUM FLOW       |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 1 - Ford-Fulkerson algorithm DST                  |" << endl;
                    cout << "| 2 - Ford-Fulkerson algorithm BST                  |" << endl;
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
                                cout << "| CHOOSE THE OPTION FOR DST FORD-FULKERSON ALGORITHM|" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "| 4 - Run the algorithm                             |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        cout << "Generate random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Ford-Fulkerson algorithm for computing maximum flow" << endl;
                                        GraphsAlgorithms::FordFulkersonAlgorithmDFS(GraphsGenerating::adjMatrix,
                                                                                    GraphsGenerating::numVertices, 0,
                                                                                    GraphsGenerating::numVertices - 1);
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
                                cout << "| CHOOSE THE OPTION FOR BST FORD-FULKERSON ALGORITHM|" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "| 4 - Run the algorithm                             |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the main menu                         |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> menuchoice;
                                cout << endl;
                                switch (menuchoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        cout << "Generate random graph" << endl;
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Ford-Fulkerson algorithm for computing maximum flow" << endl;
                                        GraphsAlgorithms::FordFulkersonAlgorithmBFS(GraphsGenerating::adjMatrix,
                                                                                    GraphsGenerating::numVertices, 0,
                                                                                    GraphsGenerating::numVertices - 1);
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
                break;
        }
    } while (menuchoice != 0);
}