#ifndef MASSSPRINGSYSTEM_H
#define MASSSPRINGSYSTEM_H

#include <Dense> //Eigen Dense
#include <Sparse> //Eigen sparse
#include <vector>

class MassSpringSystem
{
private:
    typedef Eigen::SparseMatrix<float> SparseMatrix;
    typedef Eigen::VectorXf VectorXf;
    typedef std::pair<unsigned int, unsigned int> Edge;
    typedef std::vector<Edge> Edges;

    //parameters
    unsigned int nbPoints;
    unsigned int nbSprings;
    float timeStep;
    Edges springs;
    VectorXf Vd_rest;
    VectorXf Vk;
    VectorXf Vmasses;
    VectorXf Vextf;
    float damping;

    std::vector<Eigen::Vector3f> vbuff;
public:
    MassSpringSystem(unsigned int nbPoints, unsigned int nbSprings, float timeStep, const Edges &springs, const VectorXf &Vd_rest, const VectorXf &Vk, const VectorXf &Vmasses, const VectorXf &Vextf, float damping);


    unsigned int getNbPoints() const;
    unsigned int getNbSprings() const;
    float getTimeStep() const;
    Edges getSprings() const;
    VectorXf getVd_rest() const;
    VectorXf getVk() const;
    VectorXf getVmasses() const;
    VectorXf getVextf() const;
    float getDamping() const;

    void stateToVbuff(Eigen::VectorXf state);
    void VbuffToState(Eigen::VectorXf &state);
    std::vector<Eigen::Vector3f> getVbuff() const;
    void setVbuff(const std::vector<Eigen::Vector3f> &newVbuff);
};





//#include <QVector3D>
//#include <vector>
//#include <QMatrix3x3>


//class MassParticle;
//class Spring;
//class MassSpringSystem
//{
//private:
//    std::vector<MassParticle*> particles;
//    std::vector<Spring*> springs;


//public:
//    MassSpringSystem();
//    ~MassSpringSystem();

//    MassParticle *addParticle(float mass, QVector3D position);
//    Spring *addSpring(float k, float mu, float d_rest, MassParticle* a, MassParticle *b);

//    void reset();

//    MassParticle *getParticle(int index);
//    void update(float dt);
//    void update(float dt, float prev_dt);

//    void draw();


//    std::vector<Spring *> getSprings() const;
//    std::vector<MassParticle *> getParticles() const;
//};

#endif // MASSSPRINGSYSTEM_H
