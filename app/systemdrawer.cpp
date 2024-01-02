#include "systemdrawer.h"
#include <QtOpenGL>

void SystemDrawer::draw(std::vector<Eigen::Vector3f> vbuff,
                    Edges edges)
{
    for(Edge e : edges)
    {
        Vector3f p0 = vbuff[e.first];
        Vector3f p1 = vbuff[e.second];
        drawPoint(p0); drawPoint(p1);
        drawLine(p0, p1);
    }
}

void SystemDrawer::drawPoint(Vector3f position)
{
    glColor4f(0.0, 0.5, 1.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(position[0], position[1], position[2]);
    glEnd();
}

void SystemDrawer::drawLine(Vector3f start, Vector3f end)
{
    glLineWidth(1.0);
    glColor4f(0.5, 0.0, 0.0, 1.0);

    glBegin(GL_LINES);
    glVertex3f(start[0], start[1], start[2]);
    glVertex3f(end[0], end[1], end[2]);
    glEnd();
}
