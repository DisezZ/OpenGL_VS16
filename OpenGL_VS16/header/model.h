#ifndef MODEL_H
#define MODEL_H

#include <glx.h>
#include <util.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <shader.h>
#include <mesh.h>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);

class Model
{
private:
    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTexture(aiMaterial *material, aiTextureType type, std::string typeName);
public:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    Model(std::string const& path);
    ~Model();
    void Draw(Shader &shader);
};

#endif