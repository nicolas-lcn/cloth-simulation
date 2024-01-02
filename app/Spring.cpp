#include "Spring.h"
#include "MassParticle.h"
#include <QtOpenGL>
#include <cstdio>

QVector3D Spring::getForce(MassParticle *refMass) //calculate force on refMass
{
    if(!(refMass == massA || refMass == massB)) return QVector3D(0.0, 0.0, 0.0);

    float distance = massA->getPosition().distanceToPoint(massB->getPosition());
    QVector3D direction = (massB->getPosition() - massA->getPosition());
    direction.normalize();
    // elasticity
    float springForce = k * (distance - d_rest);
    //viscosity
    float dampingForce = (mu * QVector3D::dotProduct(massB->getVelocity() - massA->getVelocity(), direction));

    return ((refMass==massA)? direction : -1.0f*direction) * (springForce + dampingForce);

}

QVector3D Spring::getDampingForce(MassParticle *refMass)
{
    QVector3D direction = (massB->getPosition() - massA->getPosition());
    direction.normalize();
    float dampingForce = (mu * QVector3D::dotProduct(massB->getVelocity() - massA->getVelocity(), direction));
    return ((refMass==massA)? direction : -1.0f*direction) * dampingForce;
}

QVector3D Spring::getSpringForce(MassParticle *refMass)
{
    float distance = massA->getPosition().distanceToPoint(massB->getPosition());
    float springForce = k * (distance - d_rest);
    QVector3D direction = (massB->getPosition() - massA->getPosition());
    direction.normalize();
    return ((refMass==massA)? direction : -1.0f*direction) * springForce;
}

void Spring::draw()
{
    glLineWidth(1.0);
    glColor4f(0.5, 0.0, 0.0, 1.0);

    glBegin(GL_LINES);
    glVertex3f(massA->getPosition().x(), massA->getPosition().y(), massA->getPosition().z());
    glVertex3f(massB->getPosition().x(), massB->getPosition().y(), massB->getPosition().z());
    glEnd();
}

const MassParticle *Spring::getMassA() const
{
    return massA;
}

const MassParticle *Spring::getMassB() const
{
    return massB;
}
