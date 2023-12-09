#include "MassParticle.h"
#include "mesh.h"
#include "Spring.h"
#include <QtOpenGL>
#include <cstdio>

QVector3D MassParticle::computeForces()
{
    QVector3D F_weight = gravity * mass;

    QVector3D F_springs = QVector3D(0.0, 0.0, 0.0); //sum of all springs;

    for(unsigned int i = 0; i<springs.size(); i++)
    {
        F_springs += springs[i]->getForce(this);
    }
    return F_springs + F_weight;
}

QVector3D MassParticle::computeDampingForces()
{
    QVector3D F_d = QVector3D(0.0, 0.0, 0.0); //sum of all springs;

    for(unsigned int i = 0; i<springs.size(); i++)
    {
        F_d += springs[i]->getDampingForce(this);
    }
    return F_d;
}

float MassParticle::computeDampingValue()
{
    float d = 0.0f; //sum of all springs;

    for(unsigned int i = 0; i<springs.size(); i++)
    {
        d += springs[i]->getMu();
    }
    return d;
}

QVector3D MassParticle::computeSpringForces()
{
    QVector3D F_springs = QVector3D(0.0, 0.0, 0.0); //sum of all springs;

    for(unsigned int i = 0; i<springs.size(); i++)
    {
        F_springs += springs[i]->getSpringForce(this);
    }
    return F_springs;
}

void MassParticle::update(float dt)
{
    if(isFixed) return;

    QVector3D forces = computeForces();
//    QVector3D sforces = computeSpringForces();
//    QVector3D F_weight = gravity * mass;
//    QVector3D forces = F_weight + sforces;
//    float d = computeDampingValue();


    QVector3D acceleration = forces/mass;

    //euler
//     position = position + velocity * dt;
//     velocity = velocity + dt * acceleration;

    // verlet
    position = 2 * position - previous + acceleration * (dt * dt);
    velocity = (position - previous)/dt;
    //previous no damping
    previous = QVector3D(position.x(), position.y(), position.z());
    // previous damping velocity

}

void MassParticle::update(float dt, float prev_dt)
{
    if(isFixed) return;

    QVector3D dforces = computeDampingForces();
    QVector3D sforces = computeSpringForces();
    QVector3D F_weight = gravity * mass;
    QVector3D forces = F_weight + sforces;
    QVector3D acceleration = forces/mass;
    velocity = velocity * dforces.length() + dt * acceleration;

    position = position + (dt/prev_dt)*(position - previous) + acceleration * ((dt+prev_dt)/2.0f)*dt;
    previous = QVector3D(position.x(), position.y(), position.z());
}

void MassParticle::draw()
{
    glColor4f(0.0, 0.5, 1.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(position.x(), position.y(), position.z());
    glEnd();
}

void MassParticle::addSpring(Spring *spring)
{
    springs.push_back(spring);
}

QVector3D MassParticle::getPrevious() const
{
    return previous;
}

void MassParticle::setPrevious(const QVector3D &newPrevious)
{
    previous = newPrevious;
}


