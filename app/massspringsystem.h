#ifndef MASSSPRINGSYSTEM_H
#define MASSSPRINGSYSTEM_H


#include <QVector3D>
#include <vector>


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

    void update(float dt);

    void draw();


};

#endif // MASSSPRINGSYSTEM_H
