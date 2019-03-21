#include "assimptest.h"

#include <QOpenGLFunctions_4_3_Core>

void  Model::loadModel(std::string path)
{

}

void Model::processNode(aiNode  *node,aiScene *scene)
{

}

void Model::processMesh(aiMesh *mesh,aiScene *scene)
{

}

QVector<Texture> Model::loadMaterialTextures(aiMaterial *mat,aiTextureType type,std::string typeName)
{
   return QVector<Texture>();
}


AssimpTest::AssimpTest(QOpenGLFunctions_4_3_Core *f,QWidget *parent)
    :BaseRender(f,parent)
{
    Assimp::Importer imp;

}

void AssimpTest::setupMesh()
{
    m_f->glGenVertexArrays(1,&m_vao);

    m_f->glGenBuffers(1,&m_vbo);
    m_f->glGenBuffers(1,&m_ebo);

    m_f->glBindVertexArray(m_vao);
    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_vbo);

    //顶点数据
    QVector<float> data;
    for(int i=0;i<m_mesh.vertices.size();i++){
        data.append(m_mesh.vertices[i].position.x());
        data.append(m_mesh.vertices[i].position.y());
        data.append(m_mesh.vertices[i].position.z());

        data.append(m_mesh.vertices[i].normal.x());
        data.append(m_mesh.vertices[i].normal.y());
        data.append(m_mesh.vertices[i].normal.y());

        data.append(m_mesh.vertices[i].texCoord.x());
        data.append(m_mesh.vertices[i].texCoord.y());
    }

    m_f->glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(float),data.data(),GL_STATIC_DRAW);

    m_f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo);
//    m_f->glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_mesh.indices * sizeof (unsigned int),m_mesh.indices.data()
//                      ,GL_STATIC_DRAW);

    //顶点位置
    m_f->glEnableVertexAttribArray(0);
    m_f->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);

    //顶点法线
    m_f->glEnableVertexAttribArray(1);
    m_f->glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);

    //纹理坐标
    m_f->glEnableVertexAttribArray(2);
    m_f->glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);

    m_f->glBindVertexArray(0);
}

void  AssimpTest::initial()
{

}

void  AssimpTest::resize(int w,int h)
{

}

void  AssimpTest::render()
{
    createProgram();
}

void AssimpTest::createProgram()
{
    m_program->loadShader(":/resources/assimp/vert.vert",":/resources/assimp/frag.frag");
    m_program->bind();

}
