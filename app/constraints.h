#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <Dense>
#include <Sparse>
#include "float.h"
class Constraint
{
protected:
    Eigen::VectorXf stiffnesses;
    typedef Eigen::Triplet<float> Triplet;
    typedef std::vector<Triplet> Triplets;
public:
    Constraint(const Eigen::VectorXf &stiffnesses);
    Constraint(const Constraint &other);
    virtual ~Constraint();
    Eigen::VectorXf getStiffnesses() const;

    virtual void EvaluateL(Triplets &LTriplets) = 0;
    virtual void EvaluateD(unsigned int index, const Eigen::VectorXf vbuff, Eigen::VectorXf &spring_dirs) = 0;
    virtual void EvaluateJ(unsigned int index, Triplets &JTriplets) = 0;

    virtual void draw(){/*do nothing*/}

    //calculate distance from click (only for fixed point)
    virtual float distance(Eigen::Vector3f p){return FLT_MAX;}
    virtual void grab(){/*do nothing*/}
    virtual void ungrab(){/*do nothing*/}
    virtual void move(Eigen::Vector3f target){/*do nothing*/}
};

class FixedPoint : public Constraint
{
private:
    unsigned int p0;
    Eigen::Vector3f fixed;

    bool isGrabbed = false;
    // Constraint interface
public:

    FixedPoint(const Eigen::VectorXf &stiffnesses);
    FixedPoint(const FixedPoint &other);
    FixedPoint(unsigned int p0, const Eigen::Vector3f &fixed, const Eigen::VectorXf &stiffnesses);
    virtual void EvaluateL(Triplets &LTriplets);
    virtual void EvaluateD(unsigned int index, const Eigen::VectorXf vbuff, Eigen::VectorXf &spring_dirs);
    virtual void EvaluateJ(unsigned int index, Triplets &JTriplets);
    virtual void draw();


    // Constraint interface
public:
    virtual float distance(Eigen::Vector3f p);
    virtual void grab();
    virtual void ungrab();
    virtual void move(Eigen::Vector3f target);


};

class SpringConstraint : public Constraint
{
protected:
    unsigned int p0, p1;
    float rest_length;

    // Constraint interface
public:
    SpringConstraint(const Eigen::VectorXf &stiffnesses);
    SpringConstraint(unsigned int p0, unsigned int p1, float rest_length, const Eigen::VectorXf &stiffnesses);
    SpringConstraint(const SpringConstraint &other);
    virtual void EvaluateL(Triplets &LTriplets);
    virtual void EvaluateD(unsigned int index, const Eigen::VectorXf vbuff, Eigen::VectorXf &spring_dirs);
    virtual void EvaluateJ(unsigned int index, Triplets &JTriplets);
};

#endif // CONSTRAINTS_H
