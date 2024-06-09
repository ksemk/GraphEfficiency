/**
 * @file SimulationOptions.cpp
 * @brief This file contains the implementation of the SimulationOptions class.
 */

#include "SimulationOptions.h"
#include "GraphsGenerating.h"
#include "graphsAlgorithms/Prim.h"
#include "graphsAlgorithms/Kruskal.h"
#include "graphsAlgorithms/Dijkstra.h"
#include "graphsAlgorithms/BellmanFord.h"
#include "graphsAlgorithms/FordFulkersonDFS.h"
#include "graphsAlgorithms/FordFulkersonBFS.h"
#include <iostream>

using namespace std;

/**
 * @brief Runs the main menu for the Graph Efficiency program.
 *
 * This function displays the main menu and handles the user's choice. The user can choose to compute the Minimum Spanning Tree (MST), compute the shortest path, compute the maximum flow, or exit the program.
 * If the user chooses to compute the MST, the runMSTMenu function is called.
 * If the user chooses to compute the shortest path, the runShortestPathMenu function is called.
 * If the user chooses to compute the maximum flow, the runMaxFlowMenu function is called.
 * If the user chooses to exit the program, a message is displayed and the function returns.
 * If the user enters an invalid choice, an error message is displayed and the menu is displayed again.
 */
void SimulationOptions::runMenu() {
    int menuchoice; // Main menu choice

    do {
        cout << "|---------------------------------------------------|" << endl;
        cout << "|                     MAIN MENU                     |" << endl;
        cout << "|---------------------------------------------------|" << endl;
        cout << "| 1 - Compute the Minimum Spanning Tree (MST)       |" << endl;
        cout << "| 2 - Compute the shortest path                     |" << endl;
        cout << "| 3 - Compute the the maximum flow                  |" << endl;
        cout << "|---------------------------------------------------|" << endl;
        cout << "| 0 - Exit the program                              |" << endl;
        cout << "|---------------------------------------------------|" << endl;
        cout << "Enter your choice: ";
        cin >> menuchoice;
        cout << endl;

        switch (menuchoice) {
            case 1: {
                int mstChoice;
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
                    cin >> mstChoice;
                    cout << endl;

                    switch (mstChoice) {
                        case 1: {
                            int primChoice;
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "|      CHOOSE THE OPTION FOR PRIM'S ALGORITHM       |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "| 4 - Run the algorithm for adjacency matrix        |" << endl;
                                cout << "| 5 - Run the algorithm for adjacency list          |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the previous menu                     |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> primChoice;
                                cout << endl;

                                switch (primChoice) {
                                    case 1:
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        randomGraphGeneratorMenu();
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Prim's algorithm for computing minimal spanning tree" << endl;
                                        Prim::TimeCounterMatrix(GraphsGenerating::adjMatrix, GraphsGenerating::numVertices);
                                        break;
                                    case 5:
                                        cout << "Run Prim's algorithm for computing minimal spanning tree" << endl;
                                        Prim::TimeCounterList(GraphsGenerating::adjList, GraphsGenerating::numVertices);
                                        break;
                                    case 0:
                                        cout << "Back to the previous menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (primChoice != 0);
                            break;
                        }
                        case 2: {
                            int kruskalChoice;
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "|     CHOOSE THE OPTION FOR KRUSKAL'S ALGORITHM     |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "| 4 - Run the algorithm for adjacency matrix        |" << endl;
                                cout << "| 5 - Run the algorithm for adjacency list          |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the previous menu                     |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> kruskalChoice;
                                cout << endl;

                                switch (kruskalChoice) {
                                    case 1:
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        randomGraphGeneratorMenu();
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Kruskal's algorithm for computing minimal spanning tree" << endl;
                                        Kruskal::TimeCounterMatrix(GraphsGenerating::adjMatrix, GraphsGenerating::numVertices, GraphsGenerating::numEdges);
                                        break;
                                    case 5:
                                        cout << "Run Kruskal's algorithm for computing minimal spanning tree" << endl;
                                        Kruskal::TimeCounterList(GraphsGenerating::adjList, GraphsGenerating::numVertices, GraphsGenerating::numEdges);
                                        break;
                                    case 0:
                                        cout << "Back to the previous menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (kruskalChoice != 0);
                            break;
                        }
                        case 0:
                            cout << "Back to the main menu" << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (mstChoice != 0);
                break;
            }
            case 2: {
                int spChoice;
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
                    cin >> spChoice;
                    cout << endl;

                    switch (spChoice) {
                        case 1: {
                            int dijkstraChoice;
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "|      CHOOSE THE OPTION FOR DIJKSTRA'S ALGORITHM   |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "| 4 - Run the algorithm for adjacency matrix        |" << endl;
                                cout << "| 5 - Run the algorithm for adjacency list          |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the previous menu                     |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> dijkstraChoice;
                                cout << endl;

                                switch (dijkstraChoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        randomGraphGeneratorMenu();
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Dijkstra's algorithm for computing shortest path" << endl;
                                        Dijkstra::TimeCounterMatrix(GraphsGenerating::adjMatrix,
                                                                    GraphsGenerating::numVertices, 0);
                                        break;
                                    case 5:
                                        cout << "Run Dijkstra's algorithm for computing shortest path" << endl;
                                        Dijkstra::TimeCounterList(GraphsGenerating::adjList,
                                                                  GraphsGenerating::numVertices, 0);
                                        break;

                                    case 0:
                                        cout << "Back to the previous menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (dijkstraChoice != 0);
                            break;
                        }
                        case 2: {
                            int bellmanFordChoice;
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "|    CHOOSE THE OPTION FOR BELLMAN-FORD ALGORITHM   |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "| 4 - Run the algorithm for adjacency matrix        |" << endl;
                                cout << "| 5 - Run the algorithm for adjacency list          |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the previous menu                     |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> bellmanFordChoice;
                                cout << endl;

                                switch (bellmanFordChoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        randomGraphGeneratorMenu();
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Bellman-Ford algorithm for computing shortest path" << endl;
                                        BellmanFord::TimeCounterMatrix(GraphsGenerating::adjMatrix, GraphsGenerating::numVertices, 0);
                                        break;
                                    case 5:
                                        cout << "Run Bellman-Ford algorithm for computing shortest path" << endl;
                                        BellmanFord::TimeCounterList(GraphsGenerating::adjList, GraphsGenerating::numVertices, 0);
                                        break;
                                    case 0:
                                        cout << "Back to the previous menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (bellmanFordChoice != 0);
                            break;
                        }
                        case 0:
                            cout << "Back to the main menu" << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (spChoice != 0);
                break;
            }
            case 3: {
                int maxFlowChoice;
                do {
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "|       CHOOSE THE ALGORITHM FOR MAXIMUM FLOW       |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 1 - Ford-Fulkerson algorithm DFS                  |" << endl;
                    cout << "| 2 - Ford-Fulkerson algorithm BFS                  |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "| 0 - Back to the main menu                         |" << endl;
                    cout << "|---------------------------------------------------|" << endl;
                    cout << "Enter your choice: ";
                    cin >> maxFlowChoice;
                    cout << endl;

                    switch (maxFlowChoice) {
                        case 1: {
                            int fordFulkersonDFSChoice;
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| CHOOSE THE OPTION FOR DST FORD-FULKERSON ALGORITHM|" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "| 4 - Run the algorithm for adjacency matrix        |" << endl;
                                cout << "| 5 - Run the algorithm for adjacency list          |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the previous menu                     |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> fordFulkersonDFSChoice;
                                cout << endl;

                                switch (fordFulkersonDFSChoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        randomGraphGeneratorMenu();
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Ford-Fulkerson algorithm for computing maximum flow" << endl;
                                        FordFulkersonDFS::TimeCounterMatrix(GraphsGenerating::adjMatrix, 0, GraphsGenerating::numVertices - 1, GraphsGenerating::numVertices);
                                        break;
                                    case 5:
                                        cout << "Run Ford-Fulkerson algorithm for computing maximum flow" << endl;
                                        FordFulkersonDFS::TimeCounterList(GraphsGenerating::adjList, 0, GraphsGenerating::numVertices - 1, GraphsGenerating::numVertices);
                                        break;
                                    case 0:
                                        cout << "Back to the previous menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (fordFulkersonDFSChoice != 0);
                            break;
                        }
                        case 2: {
                            int fordFulkersonBFSChoice;
                            do {
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| CHOOSE THE OPTION FOR BST FORD-FULKERSON ALGORITHM|" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 1 - Load graph from file                          |" << endl;
                                cout << "| 2 - Generate random graph                         |" << endl;
                                cout << "| 3 - Print existed graph                           |" << endl;
                                cout << "| 4 - Run the algorithm for adjacency matrix        |" << endl;
                                cout << "| 5 - Run the algorithm for adjacency list          |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "| 0 - Back to the previous menu                     |" << endl;
                                cout << "|---------------------------------------------------|" << endl;
                                cout << "Enter your choice: ";
                                cin >> fordFulkersonBFSChoice;
                                cout << endl;

                                switch (fordFulkersonBFSChoice) {
                                    case 1:
                                        cout << "Load graph from file" << endl;
                                        GraphsGenerating::loadGraphFromFile();
                                        break;
                                    case 2:
                                        randomGraphGeneratorMenu();
                                        break;
                                    case 3:
                                        cout << "Print existed graph" << endl;
                                        GraphsGenerating::printAdjacencyMatrix();
                                        GraphsGenerating::printAdjacencyList();
                                        break;
                                    case 4:
                                        cout << "Run Ford-Fulkerson algorithm for computing maximum flow" << endl;
                                        FordFulkersonBFS::TimeCounterMatrix(GraphsGenerating::adjMatrix, 0, GraphsGenerating::numVertices - 1, GraphsGenerating::numVertices);
                                        break;
                                    case 5:
                                        cout << "Run Ford-Fulkerson algorithm for computing maximum flow" << endl;
                                        FordFulkersonBFS::TimeCounterList(GraphsGenerating::adjList, 0, GraphsGenerating::numVertices - 1, GraphsGenerating::numVertices);
                                        break;
                                    case 0:
                                        cout << "Back to the previous menu" << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (fordFulkersonBFSChoice != 0);
                            break;
                        }
                        case 0:
                            cout << "Back to the main menu" << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (maxFlowChoice != 0);
                break;
            }
            case 0:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (menuchoice != 0);
}

/**
 * @brief Runs the menu for generating a random graph.
 *
 * This function prompts the user to enter the number of vertices and the density of the graph, then calls the generateRandomGraph function from the GraphsGenerating class to generate the graph.
 */
void SimulationOptions::randomGraphGeneratorMenu() {
    cout << "Generating random graph" << endl;
    cout << "Enter the number of vertices: ";
    int vertices;
    cin >> vertices;
    cout << endl;
    cout << "Enter the density of the graph (in %): ";
    int density;
    cin >> density;
    cout << endl;
    GraphsGenerating::generateRandomGraph(vertices, density);
}