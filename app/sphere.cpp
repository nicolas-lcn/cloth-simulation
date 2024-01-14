#include "sphere.h"
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

Sphere::Sphere(Vector3f c, float r):center(c), radius(r)
{
    //initVAO();
}

bool Sphere::isInSphere(Vector3f p, Vector3f &penetration)
{ 
    return (p-center).norm() < radius;
}

Sphere::Vector3f Sphere::getCenter() const
{
    return center;
}

void Sphere::draw()
{
//    glColor4f(0.0, 1.0, 0.0, 1.0);
//    glPointSize(5.0);
//    glBegin(GL_POINTS);
//    glVertex3f(center[0], center[1], center[2]);
//    glEnd();
//    glBindVertexArray(vao);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), nullptr);

//    glDrawArrays(GL_QUADS, 0, slices * stacks * 4);

//    glDisableClientState(GL_VERTEX_ARRAY);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

//    glutSwapBuffers();

    glBegin(GL_QUADS);

    for (int i = 0; i < slices; ++i) {
        for (int j = 0; j < stacks; ++j) {
            GLfloat theta1 = static_cast<GLfloat>(i) / slices * 2.0f * M_PI;
            GLfloat theta2 = static_cast<GLfloat>(i + 1) / slices * 2.0f * M_PI;
            GLfloat phi1 = static_cast<GLfloat>(j) / stacks * M_PI;
            GLfloat phi2 = static_cast<GLfloat>(j + 1) / stacks * M_PI;

            // Vertices for the quads
            GLfloat x1 = center.x() + radius * sin(phi1) * cos(theta1);
            GLfloat y1 = center.y() + radius * sin(phi1) * sin(theta1);
            GLfloat z1 = center.z() + radius * cos(phi1);

            GLfloat x2 = center.x() + radius * sin(phi2) * cos(theta1);
            GLfloat y2 = center.y() + radius * sin(phi2) * sin(theta1);
            GLfloat z2 = center.z() + radius * cos(phi2);

            GLfloat x3 = center.x() + radius * sin(phi2) * cos(theta2);
            GLfloat y3 = center.y() + radius * sin(phi2) * sin(theta2);
            GLfloat z3 = center.z() + radius * cos(phi2);

            GLfloat x4 = center.x() + radius * sin(phi1) * cos(theta2);
            GLfloat y4 = center.y() + radius * sin(phi1) * sin(theta2);
            GLfloat z4 = center.z() + radius * cos(phi1);
            // Draw the quad
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);
        }
    }

    glEnd();

}

float Sphere::getRadius() const
{
    return radius;
}

//void Sphere::createVBO()
//{
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    vertices = std::vector<Vertex>();

//    for (int i = 0; i < slices; ++i) {
//        for (int j = 0; j < stacks; ++j) {
//            GLfloat theta1 = static_cast<GLfloat>(i) / slices * 2.0f * M_PI;
//            GLfloat theta2 = static_cast<GLfloat>(i + 1) / slices * 2.0f * M_PI;
//            GLfloat phi1 = static_cast<GLfloat>(j) / stacks * M_PI;
//            GLfloat phi2 = static_cast<GLfloat>(j + 1) / stacks * M_PI;

//            // Vertices for the quads
//            GLfloat x1 = center.x() + radius * sin(phi1) * cos(theta1);
//            GLfloat y1 = center.y() + radius * sin(phi1) * sin(theta1);
//            GLfloat z1 = center.z() + radius * cos(phi1);

//            GLfloat x2 = center.x() + radius * sin(phi2) * cos(theta1);
//            GLfloat y2 = center.y() + radius * sin(phi2) * sin(theta1);
//            GLfloat z2 = center.z() + radius * cos(phi2);

//            GLfloat x3 = center.x() + radius * sin(phi2) * cos(theta2);
//            GLfloat y3 = center.y() + radius * sin(phi2) * sin(theta2);
//            GLfloat z3 = center.z() + radius * cos(phi2);

//            GLfloat x4 = center.x() + radius * sin(phi1) * cos(theta2);
//            GLfloat y4 = center.y() + radius * sin(phi1) * sin(theta2);
//            GLfloat z4 = center.z() + radius * cos(phi1);

//            vertices.push_back({x1, y1, z1});
//            vertices.push_back({x2, y2, z2});
//            vertices.push_back({x3, y3, z3});
//            vertices.push_back({x4, y4, z4});
//        }
//    }
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3f), vertices.data(), GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

//void Sphere::initVAO()
//{
////    glGenVertexArrays(1, &vao);
////    glBindVertexArray(vao);

////    createVBO();

////    glBindVertexArray(0);
//}
