#ifndef MESH_H
#define MESH_H

#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

#include <vector>
struct Vertex{
    GLfloat x,y,z;
};
class Mesh : protected QOpenGLFunctions
{
protected :
    GLuint vao, vbo;
    std::vector<Vertex> vertices;

public:
    virtual void draw() = 0;
    virtual void createVBO() = 0;
    virtual void initVAO() = 0;


};

#endif // MESH_H
