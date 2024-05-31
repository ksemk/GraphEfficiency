//
// Created by 10122 on 29.05.2024.
//

#ifndef GRAPHEFFICIENCY_SIMULATIONOPTIONS_H
#define GRAPHEFFICIENCY_SIMULATIONOPTIONS_H


class SimulationOptions {
public:
    static void runMenu();
private:

    static void loadGraphFromFile();

    static void printAdjacencyMatrix();

    static void printAdjacencyList();
};


#endif //GRAPHEFFICIENCY_SIMULATIONOPTIONS_H
