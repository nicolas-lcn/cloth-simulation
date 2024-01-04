#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <Dense>
#include <Sparse>
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

};

class FixedPoint : public Constraint
{
private:
    unsigned int p0;
    Eigen::Vector3f fixed;
    // Constraint interface
public:

    FixedPoint(const Eigen::VectorXf &stiffnesses);
    FixedPoint(const FixedPoint &other);
    FixedPoint(unsigned int p0, const Eigen::Vector3f &fixed, const Eigen::VectorXf &stiffnesses);
    virtual void EvaluateL(Triplets &LTriplets);
    virtual void EvaluateD(unsigned int index, const Eigen::VectorXf vbuff, Eigen::VectorXf &spring_dirs);
    virtual void EvaluateJ(unsigned int index, Triplets &JTriplets);
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
