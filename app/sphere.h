#ifndef SPHERE_H
#define SPHERE_H

#include <Dense>

class Sphere
{
private:
    typedef Eigen::Vector3f Vector3f;
    Vector3f center;
    float radius;
public:
    Sphere(Vector3f c, float r);

    bool isInSphere(Vector3f p, Vector3f &penetration); //return penetration

    Vector3f getCenter() const;

    void draw();

    float getRadius() const;



};

#endif // SPHERE_H
