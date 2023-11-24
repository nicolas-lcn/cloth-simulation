#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <QElapsedTimer>


class MassSpringSystem;
class SimulationManager
{
public:
    SimulationManager();
    ~SimulationManager();
    void initialize();
    void updateSystem();
    void drawSystem();

private:
    QElapsedTimer *deltaTimer;
    MassSpringSystem *system;
};

#endif // SIMULATIONMANAGER_H
