#ifndef MESH_H
#define MESH_H

#include <glx.h>
#include <util.h>

#include <shader.h>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
private:
    unsigned int VBO = 0, EBO = 0;
    void setupMesh();
public:
    unsigned int VAO = 0;
    std::vector<Vertex>         vertices;
    std::vector<unsigned int>   indices;
    std::vector<Texture>        textures;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();
    void Draw(Shader &shader);
};

#endif