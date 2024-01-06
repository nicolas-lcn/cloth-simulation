#include "sphere.h"
#include <QtOpenGL>

Sphere::Sphere(Vector3f c, float r):center(c), radius(r)
{

}

bool Sphere::isInSphere(Vector3f p, Vector3f &penetration)
{ 
    return (p-center).norm() < radius;
}

Sphere::Vector3f Sphere::getCenter() const
{
    return center;
}

void Sphere::draw()
{
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(center[0], center[1], center[2]);
    glEnd();
}

float Sphere::getRadius() const
{
    return radius;
}
