#ifndef QMESH_H
#define QMESH_H

#include "qmesh.h"
#include <vector>
#include <qopengl.h>
#include <QVector3D>
#include <QVector2D>
#include <QString>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
using namespace std;

struct Vertex{
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
};

struct Texture{
    GLuint id;
    QString type;
};


class QMesh
{
public:
    //QMesh(vector<Vertex> vertices_in, vector<GLuint>indices);
    QMesh(vector<Vertex> vertices_in);

    vector<Vertex> vertices;
    vector<Texture> textures;
    vector<GLuint> indices;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;

private:
    void setupMesh();
    void deleteBuffer();


};

#endif // QMESH_H
