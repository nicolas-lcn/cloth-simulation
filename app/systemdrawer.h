#ifndef SYSTEMDRAWER_H
#define SYSTEMDRAWER_H

#include <vector>
#include <Dense>


class SystemDrawer
{
private:
    typedef std::pair<unsigned int, unsigned int> Edge;
    typedef std::vector<Edge> Edges;
    typedef Eigen::Vector3f Vector3f;
    void drawPoint(Vector3f position);
    void drawLine(Vector3f start, Vector3f end);
public:
    void draw(std::vector<Eigen::Vector3f> vbuff,
         Edges edges);
    void draw(float* vbuff,
              Edges edges);
    void draw(Eigen::VectorXf vbuff,
              Edges edges);


};


#endif // SYSTEMDRAWER_H
