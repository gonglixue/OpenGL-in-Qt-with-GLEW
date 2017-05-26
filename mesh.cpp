#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(vector<Vertex> &vertices_in, vector<GLuint> &indices_in)
{
    this->vertices = vertices_in;
    this->indices = indices_in;
    qDebug() << "indices size:" << indices.size();

    this->setupMesh();
}

Mesh::Mesh(vector<Vertex> vertices_in)
{
    this->vertices = vertices_in;
    this->EBO = 0;
    qDebug() << "v_n:" <<vertices.size();
    this->setupMeshWithoutElement();
}
void Mesh::ReloadVertices(vector<Vertex> vertices_in)
{
    this->vertices.clear();
    this->vertices = vertices_in;
    qDebug() << "v_n:" << vertices.size();
    deleteBuffer();
    this->setupMeshWithoutElement();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
    qDebug() << "in setup function indices size:" << this->indices.size();
    // POSITION
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // NORMALS
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    // Texture coords
    //glEnableVertexAttribArray(2);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0); // unbind vao

}

void Mesh::setupMeshWithoutElement()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    // POSITION
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // NORMALS
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    // Texture coords
    //glEnableVertexAttribArray(2);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0); // unbind vao
}

void Mesh::deleteBuffer()
{
    qDebug() << "vbo" << VBO;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    qDebug() << "vbo-delete" << VBO;
}
