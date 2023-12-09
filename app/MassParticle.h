#include <QVector3D>
#include <mesh.h>
#include <vector>

#ifndef MASSPARTICLE_H
#define MASSPARTICLE_H


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
    QVector3D computeDampingForces();
    float computeDampingValue();
    QVector3D computeSpringForces();
    void update(float dt);
    void update(float dt, float prev_dt);

    void draw();

    void addSpring(Spring* spring);

    bool IsFixed() const;
    void setIsFixed(bool newIsFixed);
    QVector3D getPrevious() const;
    void setPrevious(const QVector3D &newPrevious);

private:
    float mass;
    QVector3D position, velocity;

    bool isFixed = false;

    std::vector<Spring*> springs;

    QVector3D gravity = QVector3D(0.0, -9.81, 0.0);

    QVector3D previous;


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
    position(position), isFixed(false), previous(QVector3D(position.x(), position.y(), position.z()))
{}

