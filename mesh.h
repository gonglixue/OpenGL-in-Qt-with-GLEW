#ifndef MESH_H
#define MESH_H

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <QDebug>
using namespace std;

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture{
    GLuint id;
    string type;
};

class Mesh
{
public:
    Mesh();
    vector<Vertex> vertices;
    vector <Texture> textures;
    vector <GLuint> indices;

    Mesh(vector<Vertex> &vertices_in, vector<GLuint> &indices_in);
    Mesh(vector<Vertex> vertices_in);
    GLuint VAO, VBO, EBO;

    void ReloadVertices(vector<Vertex> vertices_in);
private:
    void deleteBuffer();
    void setupMesh();
    void setupMeshWithoutElement();
};

#endif // MESH_H
