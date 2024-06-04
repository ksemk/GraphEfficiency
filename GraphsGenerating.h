// GraphsGenerating.h

#ifndef GRAPHEFFICIENCY_GRAPHSGENERATING_H
#define GRAPHEFFICIENCY_GRAPHSGENERATING_H

struct slistEl {
    slistEl *next;
    int v;
    int weight; // Add weight member
};

class GraphsGenerating {
public:
    static int **adjMatrix; // Macierz sąsiedztwa
    static int numVertices; // Liczba wierzchołków
    static int numEdges; // Liczba krawędzi
    static slistEl **adjList;

    static void loadGraphFromFile();
    static void printAdjacencyMatrix();
    static void printAdjacencyList();
    static void generateRandomGraph(int vertices, int density); // Declare the new function
    static void freeMemory();
};

#endif //GRAPHEFFICIENCY_GRAPHSGENERATING_H
