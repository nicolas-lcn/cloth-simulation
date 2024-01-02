
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
//#include "Spring.h"
//#include <stdio.h>

//std::vector<Spring *> MassSpringSystem::getSprings() const
//{
//    return springs;
//}

//std::vector<MassParticle *> MassSpringSystem::getParticles() const
//{
//    return particles;
//}

//MassSpringSystem::MassSpringSystem()
//{

//}

//MassSpringSystem::~MassSpringSystem()
//{
//    for(unsigned int i = 0; i<particles.size(); i++)
//    {
//        delete(particles[i]);
//    }
//    for(unsigned int i = 0; i<springs.size(); i++)
//    {
//        delete(springs[i]);
//    }
//}

//MassParticle *MassSpringSystem::addParticle(float mass, QVector3D position)
//{
//    MassParticle *particle = new MassParticle(mass, position);
//    particles.push_back(particle);
//    return particle;
//}

//Spring *MassSpringSystem::addSpring(float k, float mu, float d_rest, MassParticle *a, MassParticle *b)
//{
//    Spring *spring = new Spring(k,mu,d_rest,a,b);
//    a->addSpring(spring);
//    b->addSpring(spring);
//    springs.push_back(spring);
//    return spring;
//}

//void MassSpringSystem::reset()
//{
//    for(unsigned int i = 0; i<particles.size(); i++)
//    {
//        delete(particles[i]);
//    }
//    for(unsigned int i = 0; i<springs.size(); i++)
//    {
//        delete(springs[i]);
//    }
//    particles.clear();
//    springs.clear();
//}

//MassParticle *MassSpringSystem::getParticle(int index)
//{
//    return particles[index];
//}

//void MassSpringSystem::update(float dt)
//{
//    for(MassParticle *p : particles)
//    {
//        p->update(dt);
//    }
//}

//void MassSpringSystem::update(float dt, float prev_dt)
//{
//    for(MassParticle *p : particles)
//    {
//        p->update(dt, prev_dt);
//    }
//}

//void MassSpringSystem::draw()
//{
//    for(MassParticle *p: particles)
//    {
//        p->draw();

//    }
//    for(Spring *s : springs)
//    {
//        s->draw();

//    }

//}


