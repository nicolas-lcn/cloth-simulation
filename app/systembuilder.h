#ifndef SYSTEMBUILDER_H
#define SYSTEMBUILDER_H

#include <Dense> //eigen dense
#include <Sparse> //eigen sparse
#include <vector>

class MassSpringSystem;
class Constraint;
class SystemBuilder
{
private:
    typedef Eigen::Vector3f Vector3f;
    typedef Eigen::VectorXf VectorXf;
    typedef std::pair<unsigned int, unsigned int> Edge;
    typedef std::vector<Edge> Edges;
    typedef Eigen::Triplet<float> Triplet;
    typedef std::vector<Triplet> Triplets;
    typedef std::vector<unsigned int> Indexes;

    Indexes structI, shearI, bendI; //types of strings
    MassSpringSystem *system;

    std::vector<Eigen::Vector3f> vbuff;
    float* vertexBuffer;

public:
    void uniformGrid(
        unsigned int n,          // grid width
        float time_step,         // time step
        float rest_length,       // spring rest length (non-diagonal)
        float stiffness,         // spring stiffness
        float mass,              // node mass
        float damping_factor,    // damping factor
        float gravity,           // gravitational force (-z axis)
        int width              // cloth width
        );

    void generateVbuff(unsigned int n, int width);
    void generateVertexBuffer(unsigned int n, int width);

    Indexes getStructI() const;
    Indexes getShearI() const;
    Indexes getBendI() const;
    MassSpringSystem *getSystem() const;
    std::vector<Eigen::Vector3f> getVbuff() const;
    float *getVertexBuffer() const;


};

#endif // SYSTEMBUILDER_H
