#ifndef ASSIMPTEST_H
#define ASSIMPTEST_H

#include "baserender.h"
#include "assimp/Importer.hpp"
#include "assimp/material.h"
#include "assimp/scene.h"

struct Vertex
{
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;
};

struct Texture
{
    unsigned int id;
    std::string type;
};

//网格
struct Mesh
{
    QVector<Vertex>  vertices;
    QVector<unsigned int> indices;
    QVector<Texture> textures;

    Mesh(){}
    Mesh(const QVector<Vertex>& vert,const QVector<unsigned int>& index, const QVector<Texture>& texes){
        vertices = vert;
        indices  = index;
        textures= texes;
    }
};

class Model
{
public:
    Model(char *path){
        loadModel(path);
    }

private:
    void  loadModel(std::string path);

    //模型数据
    QVector<Mesh> m_meshes;
    std::string m_directory;

    void processNode(aiNode  *node,aiScene *scene);
    void processMesh(aiMesh *mesh,aiScene *scene);
    QVector<Texture> loadMaterialTextures(aiMaterial *mat,aiTextureType type,std::string typeName);
};

class AssimpTest : public BaseRender
{
public:
    AssimpTest(QOpenGLFunctions_4_3_Core *f,QWidget *parent);

    virtual void  initial();
    virtual void  resize(int w,int h);
    virtual void  render();

    void setupMesh();

private:
    void createProgram();

private:
    Mesh  m_mesh;

    GLuint m_vao,m_vbo,m_ebo;


};

#endif // ASSIMPTEST_H
