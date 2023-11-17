#include "MassParticle.h"
#include "Spring.h"
#include "massspringsystem.h"

MassSpringSystem::MassSpringSystem()
{

}

MassSpringSystem::~MassSpringSystem()
{
    for(unsigned int i = 0; i<particles.size(); i++)
    {
        delete(particles[i]);
    }
    for(unsigned int i = 0; i<springs.size(); i++)
    {
        delete(springs[i]);
    }
}

MassParticle *MassSpringSystem::addParticle(float mass, QVector3D position)
{
    MassParticle *particle = new MassParticle(mass, position);
    particles.push_back(particle);
    return particle;
}

Spring *MassSpringSystem::addSpring(float k, float mu, float d_rest, MassParticle *a, MassParticle *b)
{
    Spring *spring = new Spring(k,mu,d_rest,a,b);
    a->addSpring(spring);
    b->addSpring(spring);
    springs.push_back(spring);
    return spring;
}

void MassSpringSystem::update(float dt)
{
    for(MassParticle *p : particles)
    {
        p->update(dt);
    }
}

void MassSpringSystem::draw()
{
    for(MassParticle *p: particles)
    {
        p->draw();
    }
    for(Spring *s : springs)
    {
        s->draw();
    }
}
