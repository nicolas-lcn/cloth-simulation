#include "simulationmanager.h"
#include "massspringsystem.h"
#include "MassParticle.h"
#include "Spring.h"

#include <QTime>
SimulationManager::SimulationManager()
{
    system = new MassSpringSystem();
}

SimulationManager::~SimulationManager()
{

}

void SimulationManager::initialize()
{
    deltaTimer = new QElapsedTimer();
    deltaTimer->start();

    MassParticle *massFixed = system->addParticle(1, QVector3D(0.0, 0.7, 0.0));
    massFixed->setIsFixed(true);
    MassParticle *a = system->addParticle(1, QVector3D(0.1, 0.4, 0.0));
    MassParticle *b = system->addParticle(1, QVector3D(0.2, 0.5, 0.0));
    Spring *s = system->addSpring(150.0f, 50.0f, 0.1f, massFixed, a);
    Spring *s_a_b = system->addSpring(98.0, 50.0f, 0.1f, a, b);

}

void SimulationManager::updateSystem()
{
    float dt = (float) deltaTimer->elapsed() / 1000;
    float maxTimeStepValue = floor(1000.0/24.0);
    // limit dt value;
    if (dt > maxTimeStepValue / 1000.0) {
        dt = maxTimeStepValue / 1000.0;
    }
    deltaTimer->restart();

    system->update(dt);
}

void SimulationManager::drawSystem()
{
    system->draw();
}
