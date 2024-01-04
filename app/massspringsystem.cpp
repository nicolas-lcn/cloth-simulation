
#include "massspringsystem.h"

unsigned int MassSpringSystem::getNbPoints() const
{
    return nbPoints;
}

unsigned int MassSpringSystem::getNbSprings() const
{
    return nbSprings;
}

float MassSpringSystem::getTimeStep() const
{
    return timeStep;
}

MassSpringSystem::Edges MassSpringSystem::getSprings() const
{
    return springs;
}

MassSpringSystem::VectorXf MassSpringSystem::getVd_rest() const
{
    return Vd_rest;
}

MassSpringSystem::VectorXf MassSpringSystem::getVk() const
{
    return Vk;
}

MassSpringSystem::VectorXf MassSpringSystem::getVmasses() const
{
    return Vmasses;
}

MassSpringSystem::VectorXf MassSpringSystem::getVextf() const
{
    return Vextf;
}

float MassSpringSystem::getDamping() const
{
    return damping;
}

void MassSpringSystem::stateToVbuff(Eigen::VectorXf state)
{
    for(unsigned int k = 0; k<nbPoints; k++)
    {
        vbuff[k][0] = state[3*k+0];
        vbuff[k][1] = state[3*k+1];
        vbuff[k][2] = state[3*k+2];
    }
}

void MassSpringSystem::VbuffToState(VectorXf &state)
{
    for(unsigned int k = 0; k<nbPoints; k++)
    {
        state[3*k+0] = vbuff[k][0];
        state[3*k+1] = vbuff[k][1];
        state[3*k+2] = vbuff[k][2];
    }
}

std::vector<Eigen::Vector3f> MassSpringSystem::getVbuff() const
{
    return vbuff;
}

void MassSpringSystem::setVbuff(const std::vector<Eigen::Vector3f> &newVbuff)
{
    vbuff = newVbuff;
}

MassSpringSystem::MassSpringSystem(unsigned int nbPoints, unsigned int nbSprings, float timeStep, const MassSpringSystem::Edges &springs, const MassSpringSystem::VectorXf &Vd_rest, const MassSpringSystem::VectorXf &Vk, const MassSpringSystem::VectorXf &Vmasses, const MassSpringSystem::VectorXf &Vextf, float damping) : nbPoints(nbPoints),
    nbSprings(nbSprings),
    timeStep(timeStep),
    springs(springs),
    Vd_rest(Vd_rest),
    Vk(Vk),
    Vmasses(Vmasses),
    Vextf(Vextf),
    damping(damping)
{}

MassSpringSystem::~MassSpringSystem()
{

}
