#include "simulationmanager.h"
#include "massspringsystem.h"
#include "sphere.h"
#include <vector>

#include "massspringsolver.h"
#include "systembuilder.h"
#include "systemdrawer.h"
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
    //init system
    drawer = new SystemDrawer();
    sb = new SystemBuilder();
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

}

void SimulationManager::updateSystem()
{
    solver->solve(SystemParameters::iter);
    solver->solve(SystemParameters::iter);

}

void SimulationManager::drawSystem()
{
    drawer->draw(system->getVbuff(), system->getSprings());
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
    SystemParameters::k = value;
    //reset();
}

void SimulationManager::setSpringConstants(float value)
{
    SystemParameters::c_damp = value;
    //reset();
}

float SimulationManager::getK() const
{
    return SystemParameters::k;
}

float SimulationManager::getC_damp() const
{
    return SystemParameters::c_damp;
}
