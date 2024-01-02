#include "massspringsystem.h"
#include "systembuilder.h"

#include <assert.h>
#include <cstdio>


std::vector<Eigen::Vector3f> SystemBuilder::getVbuff() const
{
    return vbuff;
}

void SystemBuilder::uniformGrid(unsigned int n, float time_step, float rest_length, float stiffness, float mass, float damping_factor, float gravity, int width)
{
    //n must be odd
    assert(n % 2 ==1);

    const double root2 = 1.41421356237;

    // compute nb points and nb strings;
    unsigned int nbPoints = n*n;
    unsigned int nbSprings = (n-1) * (5 * n -2);

    //build mass list
    VectorXf masses(mass * VectorXf::Ones(nbSprings));

    //build spring list and parameters
    Edges springs(nbSprings);
    structI.reserve(2 * (n - 1) * n);
    shearI.reserve(2 * (n - 1) * (n - 1));
    bendI.reserve(n * (n - 1));

    VectorXf rest_lengths(nbSprings);
    VectorXf stiffnesses(nbSprings);
    unsigned int k = 0;
    for(unsigned int i = 0; i < n; i++)
    {
        for(unsigned int j = 0; j < n; j++)
        {
            // bottom right corner
            if(i == n - 1 && j == n - 1) {
                continue;
            }
            //bottom edge
            if (i == n - 1) {
                // structural spring
                springs[k] = Edge(n * i + j, n * i + j + 1);
                rest_lengths[k] = rest_length;
                stiffnesses[k] = stiffness;
                structI.push_back(k++);

                // bending spring
                if (j % 2 == 0) {
                    springs[k] = Edge(n * i + j, n * i + j + 2);
                    rest_lengths[k] = 2 * rest_length;
                    stiffnesses[k] = stiffness;
                    bendI.push_back(k++);
                }
                continue;
            }

            // right edge
            if (j == n - 1) {
                // structural spring
                springs[k] = Edge(n * i + j, n * (i + 1) + j);
                rest_lengths[k] = rest_length;
                stiffnesses[k] = stiffness;
                structI.push_back(k++);

                // bending spring
                if (i % 2 == 0){
                    springs[k] = Edge(n * i + j, n * (i + 2) + j);
                    rest_lengths[k] = 2 * rest_length;
                    stiffnesses[k] = stiffness;
                    bendI.push_back(k++);
                }
                continue;
            }
            // structural springs
            springs[k] = Edge(n * i + j, n * i + j + 1);
            rest_lengths[k] = rest_length;
            stiffnesses[k] = stiffness;
            structI.push_back(k++);

            springs[k] = Edge(n * i + j, n * (i + 1) + j);
            rest_lengths[k] = rest_length;
            stiffnesses[k] = stiffness;
            structI.push_back(k++);

            // shearing springs
            springs[k] = Edge(n * i + j, n * (i + 1) + j + 1);
            rest_lengths[k] = root2 * rest_length;
            stiffnesses[k] = stiffness;
            shearI.push_back(k++);

            springs[k] = Edge(n * (i + 1) + j, n * i + j + 1);
            rest_lengths[k] = root2 * rest_length;
            stiffnesses[k] = stiffness;
            shearI.push_back(k++);

            // bending springs
            if (j % 2 == 0) {
                springs[k] = Edge(n * i + j, n * i + j + 2);
                rest_lengths[k] = 2 * rest_length;
                stiffnesses[k] = stiffness;
                bendI.push_back(k++);
            }
            if (i % 2 == 0) {
                springs[k] = Edge(n * i + j, n * (i + 2) + j);
                rest_lengths[k] = 2 * rest_length;
                stiffnesses[k] = stiffness;
                bendI.push_back(k++);
            }
        }
    }

    VectorXf fext = Vector3f(0, -gravity, 0).replicate(nbPoints, 1);

    system = new MassSpringSystem(nbPoints, nbSprings, time_step,
                                  springs, rest_lengths, stiffnesses,
                                  masses, fext, damping_factor);
}

void SystemBuilder::generateVbuff(unsigned int n, int width)
{
    vbuff = std::vector<Eigen::Vector3f>(n*n);
    float step = ((float)width/(n-1));
    float x,z;
    z = (float)width/2.0f;
    for(unsigned int i = 0; i<n; i++)
    {
        x = (float)-width/2.0f;
        for(unsigned int j = 0; j<n; j++)
        {
            vbuff[n*i+j] = Eigen::Vector3f(x,0.0f,z);
            x+=(float)step;
        }
        z-=step;
    }
}

SystemBuilder::Indexes SystemBuilder::getStructI() const
{
    return structI;
}

SystemBuilder::Indexes SystemBuilder::getShearI() const
{
    return shearI;
}

SystemBuilder::Indexes SystemBuilder::getBendI() const
{
    return bendI;
}

MassSpringSystem *SystemBuilder::getSystem() const
{
    return system;
}
