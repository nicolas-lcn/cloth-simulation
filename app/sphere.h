#ifndef SPHERE_H
#define SPHERE_H

#include <QVector3D>

class Sphere
{
public:
    Sphere(QVector3D c, float r);

    bool isInSphere(QVector3D p);

    QVector3D getCenter() const;

    void draw();

    float getRadius() const;

private:
    QVector3D center;
    float radius;

};

#endif // SPHERE_H
