#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <QTimer>



class SimulationManager
{
public:
    SimulationManager();

private:
    QTimer* deltaTimer;
};

#endif // SIMULATIONMANAGER_H
