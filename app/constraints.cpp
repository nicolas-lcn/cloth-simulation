#include "constraints.h"
#include <QtOpenGL>

Eigen::VectorXf Constraint::getStiffnesses() const
{
    return stiffnesses;
}

Constraint::Constraint(const Eigen::VectorXf &stiffnesses) : stiffnesses(stiffnesses)
{}

Constraint::Constraint(const Constraint &other):stiffnesses(other.stiffnesses)
{

}

Constraint::~Constraint()
{

}

FixedPoint::FixedPoint(const Eigen::VectorXf &stiffnesses) : Constraint(stiffnesses)
{}

FixedPoint::FixedPoint(const FixedPoint &other): Constraint(other),
    p0(other.p0), fixed(other.fixed)
{

}

void FixedPoint::EvaluateL(Triplets &LTriplets)
{
    for(float ks : stiffnesses)
    {
        for(unsigned int j=0; j<3; j++)
        {
            LTriplets.push_back(Triplet(3*p0 + j, 3 * p0 + j, 1 * ks));
        }
    }
}

void FixedPoint::EvaluateD(unsigned int index, const Eigen::VectorXf vbuff, Eigen::VectorXf &spring_dirs)
{
    for(unsigned int j = 0; j<3; j++)
        spring_dirs[3 * index + j] = fixed[j];
}

void FixedPoint::EvaluateJ(unsigned int index, Triplets &JTriplets)
{
    for(float ks : stiffnesses)
        for(unsigned int j = 0 ; j < 3 ; j++)
            JTriplets.push_back(Triplet(3*p0 + j, 3 * index + j, 1 * ks));

}

void FixedPoint::draw()
{
    if(isGrabbed)
        glColor4f(0.0, 1.0, 0.0, 1.0);
    else
        glColor4f(1.0, 0.0, 0.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(fixed[0], fixed[1], fixed[2]);
    glEnd();
}

float FixedPoint::distance(Eigen::Vector3f p)
{
    return (Eigen::Vector2f(p.x(), p.y()) - Eigen::Vector2f(fixed.x(), fixed.y())).squaredNorm();
}

void FixedPoint::grab()
{
    isGrabbed = true;
}

void FixedPoint::ungrab()
{
    isGrabbed = false;
}

void FixedPoint::move(Eigen::Vector3f movement)
{
    fixed += movement;
}

SpringConstraint::SpringConstraint(const Eigen::VectorXf &stiffnesses) : Constraint(stiffnesses)
{}

SpringConstraint::SpringConstraint(unsigned int p0, unsigned int p1, float rest_length, const Eigen::VectorXf &stiffnesses) : Constraint(stiffnesses),
    p0(p0),
    p1(p1),
    rest_length(rest_length)
{}

SpringConstraint::SpringConstraint(const SpringConstraint &other):Constraint(other),
    p0(other.p0), p1(other.p1), rest_length(other.rest_length)
{

}

void SpringConstraint::EvaluateL(Triplets &LTriplets)
{

    for(float ks : stiffnesses)
    {
        for(unsigned int j=0; j<3; j++)
        {
            LTriplets.push_back(Triplet(3*p0 + j, 3 * p0 + j, 1 * ks));
            LTriplets.push_back(Triplet(3*p0 + j, 3 * p1 + j, -1 * ks));
            LTriplets.push_back(Triplet(3*p1 + j, 3 * p0 + j, -1 * ks));
            LTriplets.push_back(Triplet(3*p1 + j, 3 * p1 + j, 1 * ks));
        }
    }
}

void SpringConstraint::EvaluateD(unsigned int index, const Eigen::VectorXf vbuff, Eigen::VectorXf &spring_dirs)
{
    Eigen::Vector3f p12(
        vbuff[3 * p0 + 0] - vbuff[3 * p1 + 0],
        vbuff[3 * p0 + 1] - vbuff[3 * p1 + 1],
        vbuff[3 * p0 + 2] - vbuff[3 * p1 + 2]
        );

    p12.normalize();
    spring_dirs[3 * index + 0] = rest_length * p12[0];
    spring_dirs[3 * index + 1] = rest_length * p12[1];
    spring_dirs[3 * index + 2] = rest_length * p12[2];
}

void SpringConstraint::EvaluateJ(unsigned int index, Triplets &JTriplets)
{
    for(float ks : stiffnesses)
    {
        for(unsigned int j = 0 ; j < 3 ; j++)
        {
            JTriplets.push_back(Triplet(3*p0 + j, 3 * index + j, 1 * ks));
            JTriplets.push_back(Triplet(3*p1 + j, 3 * index + j, -1 * ks));
        }
    }
}

FixedPoint::FixedPoint(unsigned int p0, const Eigen::Vector3f &fixed, const Eigen::VectorXf &stiffnesses) : Constraint(stiffnesses),
    p0(p0),
    fixed(fixed)
{}
