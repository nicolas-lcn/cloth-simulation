#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H


namespace SystemParameters
{
    static const int n = 11;
    static const float width = 1.0f;
    static const float t = 0.008f; // timestep
    static const float r = width / (n-1);
    static float k = 1.0f;
    static const float m = 0.25;
    static float c_damp = 0.993f;
    static const float g = 9.81f * m;

    static const int iter = 5; //iterations per timestep

}


class MassSpringSystem;
class MassSpringSolver;
class SystemDrawer;
class SystemBuilder;
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
    void collisionDetection();

    float getK() const;

    float getC_damp() const;

private:

    MassSpringSystem *system;
    MassSpringSolver *solver;

    SystemDrawer *drawer;
    SystemBuilder *sb;

    Sphere *object;

};

#endif // SIMULATIONMANAGER_H
