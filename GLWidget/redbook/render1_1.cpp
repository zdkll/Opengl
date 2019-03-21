#include "render1_1.h"

#include <QDebug>

#include <QOpenGLFunctions_1_1>

Render1_1::Render1_1(QWidget *parent)
    :BaseRender(parent)
{

}

void Render1_1::initial()
{
    m_program->loadShader(":/resources/redbook/render1_1.vert",":/resources/redbook/render1_1.frag");
    m_program->bind();

    createObj();
}

void Render1_1::resize(int w, int h)
{

}

void Render1_1::render()
{
    m_f->glClear(GL_COLOR_BUFFER_BIT);

    m_f->glBindVertexArray(m_vao);
    m_f->glDrawArrays(GL_TRIANGLES,0,3);
}

void Render1_1::createObj()
{
    m_f->glGenVertexArrays(1,&m_vao);
    m_f->glBindVertexArray(m_vao);

    GLuint  vbo = 0;
    m_f->glGenBuffers(1,&vbo);
    m_f->glBindBuffer(GL_ARRAY_BUFFER,vbo);

    GLfloat data[]={-0.9,0.9
                    ,0.9,-0.9
                    ,-0.9,-0.9};

    m_f->glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);

    int vertexLoc =  m_program->attributeLocation("vetex");
    m_program->enableAttributeArray(vertexLoc);

//        m_program->setAttributeBuffer(vertexLoc,GL_FLOAT,0,2,0);
    m_f->glVertexAttribPointer(vertexLoc,2,GL_FLOAT,GL_FALSE,0,(void*)(0));
}
