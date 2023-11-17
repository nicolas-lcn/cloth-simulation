#include <QVector3D>
#include <memory>

#ifndef SPRING_H
#define SPRING_H

class Spring
{
public:
    Spring(float k, float mu, float d_rest, const MassParticle *massA, const MassParticle *massB);

    float getK() const;
    void setK(float newK);
    float getMu() const;
    void setMu(float newMu);
    float getD_rest() const;
    void setD_rest(float newD_rest);

    QVector3D getForce(MassParticle* refMass);

    void draw();


    Mesh *getMesh() const;
    void setMesh(Mesh *newMesh);

private:
    float k; //raideur
    float mu; //friction pour damping
    float d_rest; //distance au repos

    MassParticle *massA;
    MassParticle *massB;

    Mesh *mesh;

};

inline float Spring::getK() const
{
    return k;
}

inline void Spring::setK(float newK)
{
    k = newK;
}

inline float Spring::getMu() const
{
    return mu;
}

inline void Spring::setMu(float newMu)
{
    mu = newMu;
}

inline float Spring::getD_rest() const
{
    return d_rest;
}

inline void Spring::setD_rest(float newD_rest)
{
    d_rest = newD_rest;
}



#endif // SPRING_H


inline Spring::Spring(float k, float mu, float d_rest, const MassParticle *massA, const MassParticle *massB) : k(k),
    mu(mu),
    d_rest(d_rest),
    massA(massA),
    massB(massB)
{}

