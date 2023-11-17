#include "Spring.h"
#include "MassParticle.h"

QVector3D Spring::getForce(MassParticle *refMass) //calculate force on refMass
{
    if(!(refMass == massA || refMass == massB)) return QVector3D(0.0, 0.0, 0.0);

    float distance = massA->getPosition().distanceToPoint(massB->getPosition());
    QVector3D direction = (massB->getPosition() - massA->getPosition()).normalize();
    QVector3D springForce = ((refMass == massA)? k : -k) * (distance - d_rest) * direction;
    QVector3D dampingForce = ((refMass == massA)? mu : -mu) * (refMass == massA)? massA->getVelocity() : massB->getVelocity();

    return springForce + dampingForce;

}

void Spring::draw()
{
    glLineWidth(1.0);
    glColor4f(0.5, 0.0, 1.0, 1.0);

    glBegin(GL_LINES);
    glVertex3f(massA->getPosition().x, massA->getPosition().y, massA->getPosition().z);
    glVertex3f(massB->getPosition().x, massB->getPosition().y, massB->getPosition().z);
}

Mesh *Spring::getMesh() const
{
    return mesh;
}

void Spring::setMesh(Mesh *newMesh)
{
    mesh = newMesh;
}
