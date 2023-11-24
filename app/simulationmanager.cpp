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
    MassParticle *precedent = massFixed;
    float y=0.6;
    MassParticle *a, *b;
    Spring *s_p_a, *s_a_b;
    for(int i=0; i<4; i+=2)
    {
        a = system->addParticle(1, QVector3D(0.0, y, 0.0));
        y-=0.1f;
        b = system->addParticle(1, QVector3D(0.0, y, 0.0));
        y-=0.1f;
        s_p_a = system->addSpring(180.0f, 15.0f, 0.1f, precedent, a);
        s_a_b = system->addSpring(180.0, 15.0f, 0.1f, a, b);
        precedent = b;
    }


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
