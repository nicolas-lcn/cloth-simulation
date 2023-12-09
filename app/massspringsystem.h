#ifndef MASSSPRINGSYSTEM_H
#define MASSSPRINGSYSTEM_H


#include <QVector3D>
#include <vector>
#include <QMatrix3x3>


class MassParticle;
class Spring;
class MassSpringSystem
{
private:
    std::vector<MassParticle*> particles;
    std::vector<Spring*> springs;


public:
    MassSpringSystem();
    ~MassSpringSystem();

    MassParticle *addParticle(float mass, QVector3D position);
    Spring *addSpring(float k, float mu, float d_rest, MassParticle* a, MassParticle *b);

    void reset();

    MassParticle *getParticle(int index);
    void update(float dt);
    void update(float dt, float prev_dt);

    void draw();

    void computeJacobians();
    //solving linear system
    void multiplyDfDx();


    std::vector<Spring *> getSprings() const;
    std::vector<MassParticle *> getParticles() const;
};

#endif // MASSSPRINGSYSTEM_H
