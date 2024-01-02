#ifndef MASSSPRINGSOLVER_H
#define MASSSPRINGSOLVER_H

#include <Dense>//Eigen dense
#include <Sparse> //Eigen sparse
#include <vector>
#include <unordered_map>
#include <unordered_set>

class MassSpringSystem;
class MassSpringSolver
{
private:
    typedef Eigen::Vector3f Vector3f;
    typedef Eigen::VectorXf VectorXf;
    typedef Eigen::SparseMatrix<float> SparseMatrix;
    typedef Eigen::SimplicialLLT<SparseMatrix> Cholesky;
    typedef Eigen::Map<VectorXf> Map;
    typedef std::pair<unsigned int, unsigned int> Edge;
    typedef std::vector<Edge> Edges;
    typedef Eigen::Triplet<float> Triplet;
    typedef std::vector<Triplet> Triplets;

    //system
    MassSpringSystem * system;
    Cholesky matrix;

    //matrices
    SparseMatrix massMatrix; //M matrix in article
    SparseMatrix stiffnessMatrix; // L matrix in article
    SparseMatrix J; //J is used for rest_length (contains Springs indicators, indexes)

    // state
    VectorXf current; //q(n)
    VectorXf previous; //q(n-1)
    VectorXf spring_dirs;
    VectorXf inertial_term; // M * y, y = (a + 1) * q(n) - a * q(n - 1)

    // steps
    void globalStep();
    void localStep();

public:
    MassSpringSolver(MassSpringSystem* system, std::vector<Eigen::Vector3f> vbuff);
    void solve(unsigned int n);
    VectorXf& getCurrent();
};

#endif // MASSSPRINGSOLVER_H
