#ifndef GRAPHEFFICIENCY_SIMULATIONOPTIONS_H
#define GRAPHEFFICIENCY_SIMULATIONOPTIONS_H

/**
 * @class SimulationOptions
 * @brief This class provides the interface for running the simulation and generating random graphs.
 */
class SimulationOptions {
public:
    /**
     * @brief This function runs the main menu for the simulation.
     */
    static void runMenu();

private:
    /**
     * @brief This function runs the menu for generating random graphs.
     */
    static void randomGraphGeneratorMenu();
};

#endif //GRAPHEFFICIENCY_SIMULATIONOPTIONS_H