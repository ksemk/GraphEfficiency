#ifndef GRAPHSGENERATING_H
#define GRAPHSGENERATING_H

struct slistEl {
    int v;
    int weight;
    slistEl* next;
};

class GraphsGenerating {
public:
    static int** incMatrix; // Incidence matrix
    static int numVertices;
    static int numEdges;
    static slistEl** adjList;

    static void loadGraphFromFile();
    static void printIncidenceMatrix();
    static void printAdjacencyList();
    static void generateRandomGraph(int vertices, int density);
    static void freeMemory();
};

#endif // GRAPHSGENERATING_H
