#include "massspringsolver.h"
#include "massspringsystem.h"

#include <qdebug.h>

MassSpringSolver::VectorXf& MassSpringSolver::getCurrent()
{
    return current;
}

void MassSpringSolver::globalStep()
{
    float h2 = system->getTimeStep() * system->getTimeStep();

    VectorXf b = inertial_term
                 + h2 * J * spring_dirs
                 + h2 * system->getVextf();
    current = matrix.solve(b);
}

void MassSpringSolver::localStep()
{
    unsigned int j = 0;
    Edges edges = system->getSprings();
    MassSpringSolver::VectorXf rest_lengths = system->getVd_rest();
    for(Edge &e : edges)
    {
        Vector3f p12(
                current[3 * e.first + 0] - current[3 * e.second + 0],
                current[3 * e.first + 1] - current[3 * e.second + 1],
                current[3 * e.first + 2] - current[3 * e.second + 2]
            );

        p12.normalize();
        spring_dirs[3 * j + 0] = rest_lengths[j] * p12[0];
        spring_dirs[3 * j + 1] = rest_lengths[j] * p12[1];
        spring_dirs[3 * j + 2] = rest_lengths[j] * p12[2];
        j++;
    }

}

MassSpringSolver::MassSpringSolver(MassSpringSystem *system, std::vector<Eigen::Vector3f> vbuff)
    : system(system), spring_dirs(system->getNbSprings()*3)
{
    float h2 = system->getTimeStep() * system->getTimeStep();
    unsigned int nbPoints = system->getNbPoints();
    //compute current and prev states;
    VectorXf state(3*nbPoints);
    for(unsigned int k = 0; k<nbPoints; k++)
    {
        state[3*k+0] = vbuff[k][0];
        state[3*k+1] = vbuff[k][1];
        state[3*k+2] = vbuff[k][2];
    }
    current = state;
    previous = current;
    // compute Mass, Stiffness and length matrices M,
    Triplets LTriplets, JTriplets, MTriplets;

    stiffnessMatrix.resize(3*nbPoints, 3 * nbPoints);
    unsigned int k = 0 ; //springs coutner;
    for(Edge &e : system->getSprings())
    {
        for(unsigned int j=0; j<3; j++)
        {
            LTriplets.push_back(Triplet(3*e.first + j, 3 * e.first + j, 1 * system->getVk()[k]));
            LTriplets.push_back(Triplet(3*e.first + j, 3 * e.second + j, -1 * system->getVk()[k]));
            LTriplets.push_back(Triplet(3*e.second + j, 3 * e.first + j, -1 * system->getVk()[k]));
            LTriplets.push_back(Triplet(3*e.second + j, 3 * e.second + j, 1 * system->getVk()[k]));
        }
        k++;
    }
    stiffnessMatrix.setFromTriplets(LTriplets.begin(), LTriplets.end());

    J.resize(3*nbPoints, 3*system->getNbSprings());
    k=0;
    Edges edges = system->getSprings();
    for(Edge &e : edges)
    {
        for(unsigned int j = 0 ; j < 3 ; j++)
        {
            JTriplets.push_back(Triplet(3*e.first + j, 3 * k + j, 1 * system->getVk()[k]));
            JTriplets.push_back(Triplet(3*e.second + j, 3 * k + j, -1 * system->getVk()[k]));
        }
        k++;
    }
    J.setFromTriplets(JTriplets.begin(), JTriplets.end());

    massMatrix.resize(3 * nbPoints, 3* nbPoints);
    for(unsigned int i = 0; i < nbPoints; i++)
    {
        for(unsigned int j = 0; j< 3; j++)
            MTriplets.push_back(Triplet(3*i+j, 3*i+j, system->getVmasses()[i] ));
    }
    massMatrix.setFromTriplets(MTriplets.begin(), MTriplets.end());

    //pre-factor system matrix
    SparseMatrix A = massMatrix + h2 * stiffnessMatrix;
    matrix.compute(A);
}

void MassSpringSolver::solve(unsigned int n)
{
    float a = system->getDamping();

    inertial_term = massMatrix * ((a+1) * current - a * previous);

    previous = current;

    for(unsigned int i = 0; i<n; i++)
    {
        localStep();
        globalStep();
    }


    system->stateToVbuff(current);

}
