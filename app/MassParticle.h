#include <QVector3D>
#include <mesh.h>
#include <vector>

#ifndef MASSPARTICLE_H
#define MASSPARTICLE_H

class Mesh;
class Spring;
class MassParticle{
public:
    MassParticle(float mass, const QVector3D &position);

    float getMass() const;
    void setMass(float newMass);
    QVector3D getPosition() const;
    void setPosition(const QVector3D &newPosition);
    QVector3D getVelocity() const;
    void setVelocity(const QVector3D &newVelocity);

    QVector3D computeForces(); //gravity & springs
    void update(float dt);

    void draw();

    void addSpring(Spring* spring);


    const Mesh *getMesh() const;
    void setMesh(const Mesh *newMesh);

    bool IsFixed() const;
    void setIsFixed(bool newIsFixed);

private:
    float mass;
    QVector3D position, velocity;

    const Mesh *mesh;

    bool isFixed = false;

    std::vector<Spring*> springs;

    QVector3D gravity = QVector3D(0.0, -9.81, 0.0);


};

inline float MassParticle::getMass() const
{
    return mass;
}

inline void MassParticle::setMass(float newMass)
{
    mass = newMass;
}

inline QVector3D MassParticle::getPosition() const
{
    return position;
}

inline void MassParticle::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}

inline QVector3D MassParticle::getVelocity() const
{
    return velocity;
}

inline void MassParticle::setVelocity(const QVector3D &newVelocity)
{
    velocity = newVelocity;
}

inline const Mesh *MassParticle::getMesh() const
{
    return mesh;
}

inline void MassParticle::setMesh(const Mesh* newMesh)
{
    mesh = newMesh;
}

inline bool MassParticle::IsFixed() const
{
    return isFixed;
}

inline void MassParticle::setIsFixed(bool newIsFixed)
{
    isFixed = newIsFixed;
}

#endif // MASSPARTICLE_H


inline MassParticle::MassParticle(float mass, const QVector3D &position) : mass(mass),
    position(position), isFixed(false)
{}

