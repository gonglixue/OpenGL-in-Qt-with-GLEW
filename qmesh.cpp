#include "qmesh.h"
#include <QDebug>
QMesh::QMesh()
{

}

QMesh::QMesh(vector<Vertex> &vertices_in)
{


    this->vertices = vertices_in;
    qDebug() << "v_n" << vertices.size();
    //this->VBO = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //this->setupMesh();

}

QMesh::QMesh(vector<Vertex> &vertices_in, vector<GLuint> &indices_in)
{

    this->vertices = vertices_in;
    this->indices = indices_in;
    qDebug() << "v_n" << vertices.size();
    qDebug() << "i_n" << indices.size();
    //this->VBO = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //this->EBO = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

}

void QMesh::setupMesh()
{
/*
    this->VAO.create();
    this->VBO.create();
    //QOpenGLVertexArrayObject::Binder VAO_binder(&VAO);  //?? bind VAO

    VAO.bind();
    VBO.bind();
    VBO.allocate(&this->vertices[0], this->vertices.size()*sizeof(Vertex));

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    // POSITION
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(0));
    // NORMALS
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Normal)));
    // TEXCOORDS
    //f->glEnableVertexAttribArray(2);
    //f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, TexCoords)));

    //this->VBO.release();  // unbind
    this->VAO.release();
*/
}

void QMesh::setupMeshWithIndices()
{
    /*
    this->VAO.create();
    this->VBO.create();
    this->EBO.create();
    //QOpenGLVertexArrayObject::Binder VAO_binder(&VAO);

    VAO.bind();
    VBO.bind();
    VBO.allocate(&this->vertices[0], this->vertices.size()*sizeof(Vertex));
    EBO.bind();
    EBO.allocate(&this->indices[0], this->indices.size()*sizeof(GLuint));

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    // POSITION
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(0));
    // NORMALS
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Normal)));
    // TEXCOORDS
    //f->glEnableVertexAttribArray(2);
    //f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, TexCoords)));

    //this->VBO.release();  // unbind
    this->VAO.release();
    */
}

void QMesh::deleteBuffer()
{
/*
    this->VAO.destroy();
    this->VBO.destroy();
*/
}

