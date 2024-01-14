#ifndef SPHERE_H
#define SPHERE_H

#include "Mesh.h"
#include <Dense>



class Sphere /*: public Mesh*/
{
private:
    typedef Eigen::Vector3f Vector3f;
    Vector3f center;
    float radius;

    //draw
    const int slices = 30;  // Number of slices
    const int stacks = 30;  // Number of stacks


public:
    Sphere(Vector3f c, float r);

    bool isInSphere(Vector3f p, Vector3f &penetration); //return penetration

    Vector3f getCenter() const;

    float getRadius() const;
    void draw();





    // Mesh interface
//public:
//    virtual void draw();
//    virtual void createVBO();
//    virtual void initVAO();
};

#endif // SPHERE_H
