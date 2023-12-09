#include "simulationmanager.h"
#include "massspringsystem.h"
#include "MassParticle.h"
#include "Spring.h"
#include "sphere.h"
#include <vector>

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
    previous_dt = 0.0f;

//    MassParticle *massFixed = system->addParticle(1, QVector3D(-0.5, 0.0, 0.0));
//    massFixed->setIsFixed(true);
//    MassParticle *endFixed = system->addParticle(1, QVector3D(0.5, 0.0, 0.0));
//    endFixed->setIsFixed(true);
//    MassParticle *precedent = massFixed;
//    float y=-0.4;
//    MassParticle *a, *b;
//    Spring *s_p_a, *s_a_b;
//    for(int i=0; i<8; i+=2)
//    {
//        a = system->addParticle(1, QVector3D(y, 0, 0.0));
//        y+=1.0f/8.0f;
//        b = system->addParticle(1, QVector3D(y, 0, 0.0));
//        y+=1.0f/8.0f;
//        s_p_a = system->addSpring(1.0f, 1.0f, 0.1f, precedent, a);
//        s_a_b = system->addSpring(1.0f, 1.0f, 0.1f, a, b);
//        precedent = b;
//    }
//    system->addSpring(1.0f, 1.0f, 0.1f, precedent, endFixed);

    //particles grid
    std::vector<std::vector<MassParticle*>> grid = std::vector<std::vector<MassParticle*>>();
    float x;
    int width,height;
    width = height = 16;
    float nbParticles = width * height;
    for(int i = 0; i<height; i++)
    {
        grid.push_back(std::vector<MassParticle*>());
        for(int j = 0; j<width; j++)
        {
            x = (float)j*1.0f/(float)width - 0.8f;
            MassParticle *m = system->addParticle(1.0f, QVector3D(x,0.9,0.0f));
            grid[i].push_back(m);
        }
    }
    //strings
    for(int i=0; i<height-1; i++)
    {
        for(int j=0; j<width-1; j++)
        {
            //structural
            system->addSpring(k, c_damp, 0.02f, grid[i][j], grid[i+1][j]);
            system->addSpring(k, c_damp, 0.02f, grid[i][j], grid[i][j+1]);

            //shear
            system->addSpring(kshear, c_damp, 0.02f * sqrt(2), grid[i][j], grid[i+1][j+1]);
            system->addSpring(kshear, c_damp, 0.02f * sqrt(2), grid[i+1][j], grid[i][j+1]);

            //bending
            if(i+2<height)system->addSpring(kbend, c_damp, 0.04f, grid[i][j], grid[i+2][j]);
            if(j+2<width)system->addSpring(kbend, c_damp, 0.04f, grid[i][j], grid[i][j+2]);
        }
    }
//    // last column springs
    for(int i =1; i<height; i++)
    {
        system->addSpring(k, 0.3f, 0.02f, grid[i-1][width-1], grid[i][width-1]);
        if(i>1)system->addSpring(kbend, c_damp, 0.04f, grid[i-2][width-1], grid[i][width-1]);
    }
    // last row springs
    for(int i =1; i<width; i++)
    {
        system->addSpring(k, c_damp, 0.02f, grid[height-1][i-1], grid[height-1][i]);
        if(i>1)system->addSpring(kbend, c_damp, 0.04f, grid[height-1][i-2], grid[height-1][i]);
    }
    grid[0][0]->setIsFixed(true);
    grid[0][width-1]->setIsFixed(true);

    object = new Sphere(QVector3D(-0.5f, 0.0, 0.0), 0.5f);


}

void SimulationManager::updateSystem()
{
    float dt = (float) deltaTimer->elapsed() / 1000;
    float maxTimeStepValue = floor(1000.0/60.0);
    // limit dt value;
    if (dt > maxTimeStepValue / 1000.0) {
        dt = maxTimeStepValue / 1000.0;
    }
    deltaTimer->restart();
    handleCollisions(object);
    system->update(dt);
    //system->update(dt, previous_dt);
    previous_dt = dt;
}

void SimulationManager::drawSystem()
{
    system->draw();
    object->draw();
}

void SimulationManager::reset()
{
    system->reset();
    initialize();
}

void SimulationManager::setDampingConstants(float value)
{
    std::vector<Spring*> springs = system->getSprings();
    for(Spring *s : springs)
    {
        s->setMu(value);
    }
}

void SimulationManager::setSpringConstants(float value)
{
    std::vector<Spring*> springs = system->getSprings();
    for(Spring *s: springs)
    {
        s->setK(value);
    }
}

bool SimulationManager::detectCollisions(Sphere *sphere, MassParticle* m)
{
    return sphere->isInSphere(m->getPosition());
}

void SimulationManager::handleCollisions(Sphere *sphere)
{
    std::vector<MassParticle*> particles = system->getParticles();
    for(MassParticle* m : particles)
    {
        if(detectCollisions(sphere, m))
        {
            QVector3D n = sphere->getCenter() - m->getPosition();
            n.normalize();
            float Crm = 1.0f;
            float jm = -(1+Crm)*(QVector3D::dotProduct(m->getVelocity(), n)) * (1.0f / (1.0/m->getMass() + 1.0f));
            m->setVelocity(m->getVelocity() + (jm/m->getMass()) * n);
        }
    }
}
