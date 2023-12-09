#include "MassParticle.h"
#include "Spring.h"
#include "massspringsystem.h"
#include <stdio.h>

std::vector<Spring *> MassSpringSystem::getSprings() const
{
    return springs;
}

std::vector<MassParticle *> MassSpringSystem::getParticles() const
{
    return particles;
}

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

void MassSpringSystem::reset()
{
    for(unsigned int i = 0; i<particles.size(); i++)
    {
        delete(particles[i]);
    }
    for(unsigned int i = 0; i<springs.size(); i++)
    {
        delete(springs[i]);
    }
    particles.clear();
    springs.clear();
}

MassParticle *MassSpringSystem::getParticle(int index)
{
    return particles[index];
}

void MassSpringSystem::update(float dt)
{
    for(MassParticle *p : particles)
    {
        p->update(dt);
    }
}

void MassSpringSystem::update(float dt, float prev_dt)
{
    for(MassParticle *p : particles)
    {
        p->update(dt, prev_dt);
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

void MassSpringSystem::computeJacobians()
{
    int nb_springs = (int)springs.size();
    for(int i=0; i<nb_springs; i++)
    {
        QVector3D dx = springs[i]->getMassA()->getPosition() - springs[i]->getMassB()->getPosition();
        QMatrix3x3 dxtdx, i3x3;
        //outer-product;
        for(int n = 0; n<3; n++)
        {
            for(int m = 0; m<3; m++)
            {
                dxtdx(n,m)= dx[n] * dx[m];
            }
        }
        i3x3.setToIdentity();
        double l = sqrt(QVector3D::dotProduct(dx,dx));
        if(l!=0.0) l = 1.0/l;
        dxtdx=dxtdx*(l*l);

        springs[i]->setJx((dxtdx + (i3x3-dxtdx) * (l-springs[i]->getD_rest() * l)) * (springs[i]->getK()));
        springs[i]->setJv(i3x3);
        springs[i]->setJv(springs[i]->getJv() * springs[i]->getMu());

    }
}
