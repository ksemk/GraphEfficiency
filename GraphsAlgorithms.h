//
// Created by 10122 on 29.05.2024.
//

#ifndef GRAPHEFFICIENCY_GRAPHSALGORITHMS_H
#define GRAPHEFFICIENCY_GRAPHSALGORITHMS_H


class GraphsAlgorithms {
public:
    static void PrimsAlgorithm(int **adjMatrix, int numVertices);
    static void KruskalsAlgorithm(int **adjMatrix, int numVertices);
    static void DijkstrasAlgorithm(int **adjMatrix, int numVertices, int startVertex);
    static void BellmanFordAlgorithm(int **adjMatrix, int numVertices, int startVertex);
    static void FordFulkersonAlgorithmDFS(int **adjMatrix, int numVertices, int startVertex, int endVertex);
    static void FordFulkersonAlgorithmBFS(int **adjMatrix, int numVertices, int startVertex, int endVertex);
};



#endif //GRAPHEFFICIENCY_GRAPHSALGORITHMS_H
