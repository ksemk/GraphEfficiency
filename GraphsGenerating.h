//
// Created by 10122 on 31.05.2024.
//

#ifndef GRAPHEFFICIENCY_GRAPHSGENERATING_H
#define GRAPHEFFICIENCY_GRAPHSGENERATING_H


class GraphsGenerating {

public:
    static int **adjMatrix; // Macierz sąsiedztwa
    static int numVertices; // Liczba wierzchołków
    static int numEdges; // Liczba krawędzi
    static void loadGraphFromFile();

    static void printAdjacencyMatrix();

    static void printAdjacencyList();

    static void freeMemory();

};


#endif //GRAPHEFFICIENCY_GRAPHSGENERATING_H
