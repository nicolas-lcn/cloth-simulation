#include "massspringsolver.h"
#include "massspringsystem.h"
#include "constraints.h"
#include "systembuilder.h"

#include <qdebug.h>

MassSpringSolver::VectorXf& MassSpringSolver::getCurrent()
{
    return current;
}

std::vector<Constraint *> MassSpringSolver::getConstraints() const
{
    return constraints;
}

void MassSpringSolver::setConstraints(const std::vector<Constraint *> &newConstraints)
{
    constraints = newConstraints;
}

void MassSpringSolver::computeMatrices()
{
    float h2 = system->getTimeStep() * system->getTimeStep();
    unsigned int nbPoints = system->getNbPoints();
    // compute Mass, Stiffness and length matrices M,
    Triplets LTriplets, JTriplets, MTriplets;

    stiffnessMatrix.resize(3*nbPoints, 3 * nbPoints);
    for (unsigned int index = 0; index < constraints.size(); index++)
    {
        constraints[index]->EvaluateL(LTriplets);
    }
    stiffnessMatrix.setFromTriplets(LTriplets.begin(), LTriplets.end());

    J.resize(3*nbPoints, 3 * constraints.size());
    JTriplets.clear();
    for (unsigned int index = 0; index < constraints.size(); index++)
    {
        constraints[index]->EvaluateJ(index, JTriplets);
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

void MassSpringSolver::setupConstraints(SystemBuilder *sb, int n)
{
    constraints = std::vector<Constraint*>();

     //fixed point constraints
    constraints.push_back(new FixedPoint(0, system->getVbuff()[0], system->getVk()));
    constraints.push_back(new FixedPoint(n-1, system->getVbuff()[n-1], system->getVk()));

//    //struct spring constraints
//    for(unsigned int i = 0; i<sb->getStructI().size(); i++)
//    {
//        Edge e = system->getSprings()[i];
//        constraints.push_back(new SpringConstraint(e.first, e.second, system->getVd_rest()[i], system->getVk()));
//    }
//    //bend spring constraints
//    for(unsigned int i = 0; i<sb->getBendI().size(); i++)
//    {
//        Edge e = system->getSprings()[i];
//        constraints.push_back(new SpringConstraint(e.first, e.second, system->getVd_rest()[i], system->getVk()));
//    }
    unsigned int i = 0;
    for(Edge e : system->getSprings())
    {
        constraints.push_back(new SpringConstraint(e.first, e.second, system->getVd_rest()[i], system->getVk()));
        i++;
    }
}

void MassSpringSolver::clearConstraints()
{
    for (unsigned int i = 0; i < constraints.size(); ++i)
    {
        delete constraints[i];
    }
    constraints.clear();
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
    spring_dirs.resize(3 * constraints.size());
    spring_dirs.setZero(3 * constraints.size());
    for (unsigned int index = 0; index < constraints.size(); index++)
    {
        constraints[index]->EvaluateD(index, current, spring_dirs);
    }
}

MassSpringSolver::MassSpringSolver(MassSpringSystem *system, std::vector<Eigen::Vector3f> vbuff)
    : system(system),
    spring_dirs(system->getNbSprings()*3)
{
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

