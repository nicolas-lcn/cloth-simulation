#include "sphere.h"
#include <QtOpenGL>

Sphere::Sphere(QVector3D c, float r):center(c), radius(r)
{

}

bool Sphere::isInSphere(QVector3D p)
{
    return (p-center).length()<=radius;
}

QVector3D Sphere::getCenter() const
{
    return center;
}

void Sphere::draw()
{
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(center.x(), center.y(), center.z());
    glEnd();
}
