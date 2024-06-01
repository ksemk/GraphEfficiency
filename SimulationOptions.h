//
// Created by 10122 on 29.05.2024.
//

#ifndef GRAPHEFFICIENCY_SIMULATIONOPTIONS_H
#define GRAPHEFFICIENCY_SIMULATIONOPTIONS_H


class SimulationOptions {
public:
    static void runMenu();

private:
    void displayMainMenu();
    void handleMainMenuChoice(int choice);
    void displayMSTMenu();
    void handleMSTChoice(int choice);
    void displayShortestPathMenu();
    void handleShortestPathChoice(int choice);
    void displayMaxFlowMenu();
    void handleMaxFlowChoice(int choice);
    void loadGraph();
    void generateRandomGraph();
    void printGraph();
};



#endif //GRAPHEFFICIENCY_SIMULATIONOPTIONS_H
