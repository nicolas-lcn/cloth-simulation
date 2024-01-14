#include "simulationmanager.h"
#include "massspringsystem.h"
#include "sphere.h"
#include <vector>

#include "massspringsolver.h"
#include "sphere.h"
#include "systembuilder.h"
#include "systemdrawer.h"
#include "constraints.h"
#include <ostream>
#include <QTime>
#include <QDebug>
SimulationManager::SimulationManager()
{

}

SimulationManager::~SimulationManager()
{

}

void SimulationManager::initialize()
{
    //Print Paramaters
    qDebug()<<"System Parameters";
    qDebug()<<"System stiffness : "<<SystemParameters::k;
    qDebug()<<"System damping : "<<SystemParameters::c_damp;
    //init system
    drawer = new SystemDrawer();
    sb = new SystemBuilder();
    qDebug()<<"Initializing...";
    sb->uniformGrid(
        SystemParameters::n,
        SystemParameters::t,
        SystemParameters::r,
        SystemParameters::k,
        SystemParameters::m,
        SystemParameters::c_damp,
        SystemParameters::g,
        (int)SystemParameters::width
        );
    system = sb->getSystem();
    sb->generateVbuff(SystemParameters::n, SystemParameters::width);
    std::vector<Eigen::Vector3f> vbuff = sb->getVbuff();
    system->setVbuff(vbuff);

    //init solver
    solver = new MassSpringSolver(system, system->getVbuff());
    solver->setupConstraints(sb, SystemParameters::n);
    solver->computeMatrices();
    object = new Sphere(Eigen::Vector3f(0.0f, 0.0f, 0.0f), 0.2f);

}

void SimulationManager::updateSystem()
{
    solver->solve(SystemParameters::iter);
    solver->solve(SystemParameters::iter);
    if(isDetectionToggleOn) collisionDetection();

}

void SimulationManager::drawSystem()
{
    drawer->draw(system->getVbuff(), system->getSprings());
    if(isDetectionToggleOn) object->draw();
}

void SimulationManager::reset()
{
//    system->reset();
    delete system;
    solver->clearConstraints();

    initialize();
}

void SimulationManager::setDampingConstants(float value)
{
    SystemParameters::c_damp = value;
    //reset();
}

void SimulationManager::setSpringConstants(float value)
{
    SystemParameters::k = value;
    //reset();
}

void SimulationManager::collisionDetection()
{
    //Eigen::VectorXf penetration(system->getNbPoints()*3);
    for(unsigned int i = 0; i<system->getNbPoints(); i++)
    {
//        Eigen::Vector3f i_pen;
//        if(object->isInSphere(system->getVbuff()[i], i_pen))
//        {
//            //qDebug()<<"Collides "<<system->getVbuff()[i][0]<<" "<<system->getVbuff()[i][1]<<" "<<system->getVbuff()[i][2];
//            penetration[3*i+0] = i_pen[0];
//            penetration[3*i+1] = i_pen[1];
//            penetration[3*i+2] = i_pen[2];
//        }
        system->handleSphereCollision(object->getCenter(), object->getRadius(), i);
        //else qDebug()<<"Not collide "<<system->getVbuff()[i][0]<<" "<<system->getVbuff()[i][1]<<" "<<system->getVbuff()[i][2];
    }
//    std::vector<Eigen::Vector3f> positions(system->getVbuff());
//    for(unsigned int i = 0; i<system->getNbPoints(); i++)
//    {
//        Eigen::Vector3f pen(penetration[3*i+0], penetration[3*i+1], penetration[3*i+2]);
//        //qDebug()<<pen[0]<<" "<<pen[1]<<" "<<pen[2];
//        //qDebug()<<system->getVbuff()[i][0]<<" "<<system->getVbuff()[i][1]<<" "<<system->getVbuff()[i][2];
//        positions[i] -= pen;
//        //qDebug()<<"After pen"<<pen.norm()<<" "<<system->getVbuff()[i][0]<<" "<<system->getVbuff()[i][1]<<" "<<system->getVbuff()[i][2];
//    }
//    system->setVbuff(positions);
    system->VbuffToState(solver->getCurrent());

}

void SimulationManager::drawConstraints()
{
    for(Constraint * c : solver->getConstraints())
    {
        c->draw();
    }
}

float SimulationManager::getK() const
{
    return SystemParameters::k;
}

float SimulationManager::getC_damp() const
{
    return SystemParameters::c_damp;
}

void SimulationManager::handleClick(float x, float y, float z)
{
    float minDist = FLT_MAX;
    if(selectedConstraint != -1)
        solver->getConstraints()[selectedConstraint]->ungrab();
    unsigned int best_candidate = -1;
    for(unsigned int i = 0; i<solver->getConstraints().size(); i++)
    {
        Constraint *c = solver->getConstraints()[i];
        float dist = c->distance(Eigen::Vector3f(x,y,0.0f));
        if(dist < minDist)
        {
            minDist = dist;
            best_candidate = i;
        }
    }
    if(best_candidate !=-1)
    {
        selectedConstraint = best_candidate;
        solver->getConstraints()[selectedConstraint]->grab();
    }
}

void SimulationManager::handleMouvement(float dx, float dy, float dz)
{
    solver->getConstraints()[selectedConstraint]->move(Eigen::Vector3f(dx,dy, dz));
}

void SimulationManager::addConstraint(float x, float y, float z)
{
}

void SimulationManager::setIsDetectionToggleOn(bool newIsDetectionToggleOn)
{
    isDetectionToggleOn = newIsDetectionToggleOn;
}
