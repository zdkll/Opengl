#include "texture.h"

#define Vertex_Location  0
#define Color_Location   1
#define Texc_Location     2

Texture::Texture(QOpenGLFunctions_4_3_Core *f,QObject *parent)
    :BaseRender(f,parent),m_texture(QOpenGLTexture::Target2D)
{

}

void Texture::initial()
{
    createProgram();

    makeObj();
}

void  Texture::resize(int w,int h)
{

}

void  Texture::render()
{
    m_f->glEnableVertexAttribArray(Vertex_Location);
    m_f->glEnableVertexAttribArray(Color_Location);
    m_f->glEnableVertexAttribArray(Texc_Location);

    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_Vbo);
    m_f->glVertexAttribPointer(Vertex_Location,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),0);
    m_f->glVertexAttribPointer(Color_Location,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
    m_f->glVertexAttribPointer(Texc_Location,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(void*)(6*sizeof(GLfloat)));

    m_texture.bind();
    m_f->glDrawArrays(GL_TRIANGLE_FAN,0,4);

    m_f->glDisableVertexAttribArray(Vertex_Location);
    m_f->glDisableVertexAttribArray(Color_Location);
    m_f->glDisableVertexAttribArray(Texc_Location);
}

void Texture::createProgram()
{
    m_program->loadShader(":/resources/texture/vert.vert",":/resources/texture/frag.frag");
    m_program->bind();

    m_program->bindAttributeLocation("Vertex",Vertex_Location);
    m_program->bindAttributeLocation("Color",Color_Location);
    m_program->bindAttributeLocation("Texc",Texc_Location);

}

void Texture::makeObj()
{
    //m_texture.set
    m_texture.setData(QImage(":/resources/texture/container.jpg").mirrored(),QOpenGLTexture::DontGenerateMipMaps);

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    m_f->glGenBuffers(1,&m_Vbo);
    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_Vbo);
    m_f->glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

}
