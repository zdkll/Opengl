#include "texture.h"

#define Vertex_Location  0
#define Color_Location   1
#define Texc_Location     2

Texture::Texture(QOpenGLFunctions_4_3_Core *f,QWidget *parent)
    :BaseRender(f,parent),m_texture1(QOpenGLTexture::Target2D)
    ,m_texture2(QOpenGLTexture::Target2D)
{
    m_mixFactor = 0.2;
}

void Texture::initial()
{
    createProgram();

    makeObj();
}

void  Texture::resize(int w,int h)
{

}

void Texture::render()
{
    m_f->glUniform1f(m_mixFacLocation,m_mixFactor);

    m_f->glEnableVertexAttribArray(Vertex_Location);
    m_f->glEnableVertexAttribArray(Color_Location);
    m_f->glEnableVertexAttribArray(Texc_Location);

    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_Vbo);
    m_f->glVertexAttribPointer(Vertex_Location,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),0);
    m_f->glVertexAttribPointer(Color_Location,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
    m_f->glVertexAttribPointer(Texc_Location,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(void*)(6*sizeof(GLfloat)));

    //激活纹理单元，绑定纹理对象到激活的纹理单元
    m_f->glActiveTexture(GL_TEXTURE0);
    m_texture1.bind();
    m_f->glActiveTexture(GL_TEXTURE1);
    m_texture2.bind();

    m_f->glDrawArrays(GL_TRIANGLE_FAN,0,4);

    m_f->glDisableVertexAttribArray(Vertex_Location);
    m_f->glDisableVertexAttribArray(Color_Location);
    m_f->glDisableVertexAttribArray(Texc_Location);
}

void Texture::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up || e->key() == Qt::Key_Down){
        m_mixFactor = e->key() == Qt::Key_Up?(m_mixFactor+0.02):(m_mixFactor-0.02);
        m_mixFactor = std::min<float>(m_mixFactor,1.0);
        m_mixFactor = std::max<float>(m_mixFactor,0.0);
        m_widget->update();
    }
}

void Texture::createProgram()
{
    m_program->loadShader(":/resources/texture/vert.vert",":/resources/texture/frag.frag");

    m_program->bind();
    //设置采样器到对应纹理单元
    qDebug()<<m_program->uniformLocation("Texture1");
    m_program->setUniformValue(m_program->uniformLocation("Texture1"),0);
    m_program->setUniformValue(m_program->uniformLocation("Texture2"),1);

    m_program->bindAttributeLocation("Vertex",Vertex_Location);
    m_program->bindAttributeLocation("Color",Color_Location);
    m_program->bindAttributeLocation("Texc",Texc_Location);

    m_mixFacLocation = m_f->glGetUniformLocation(m_program->programId(),"MixFactor");
}

void Texture::makeObj()
{
    //m_texture.set
    m_texture1.setData(QImage(":/resources/texture/container.jpg").mirrored(),QOpenGLTexture::DontGenerateMipMaps);
    m_texture2.setData(QImage(":/resources/texture/awesomeface.png").mirrored(),QOpenGLTexture::DontGenerateMipMaps);

    m_f->glBindTexture(GL_TEXTURE_2D,m_texture1.textureId());
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    m_f->glBindTexture(GL_TEXTURE_2D,m_texture2.textureId());
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // 左上
    };

    m_f->glGenBuffers(1,&m_Vbo);
    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_Vbo);
    m_f->glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
}
