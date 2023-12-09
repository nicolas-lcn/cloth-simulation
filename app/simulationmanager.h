#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <QElapsedTimer>


class MassSpringSystem;
class MassParticle;
class Sphere;
class SimulationManager
{
public:
    SimulationManager();
    ~SimulationManager();
    void initialize();
    void updateSystem();
    void drawSystem();
    void reset();
    void setDampingConstants(float value);
    void setSpringConstants(float value);
    bool detectCollisions(Sphere* sphere, MassParticle* m);
    void handleCollisions(Sphere* sphere);

private:
    QElapsedTimer *deltaTimer;
    MassSpringSystem *system;
    float previous_dt;
    float k = 100.0f;
    float kshear = k;
    float kbend = k;
    float c_damp = 0.993f;

    Sphere* object;
};

#endif // SIMULATIONMANAGER_H
