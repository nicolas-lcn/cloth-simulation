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

void MassParticle::update(float dt)
{
    if(isFixed) return;

    QVector3D forces = computeForces();
    QVector3D acceleration = forces/mass;

    velocity = velocity + dt * acceleration;
    position = position + velocity * dt;
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
