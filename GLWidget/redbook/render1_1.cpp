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
    //    m_f->glDrawArrays(GL_TRIANGLES,0,3);
    m_f->glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void Render1_1::createObj()
{
    m_f->glGenVertexArrays(1,&m_vao);
    m_f->glBindVertexArray(m_vao);

    GLuint  vbo[2];
    m_f->glGenBuffers(2,vbo);
    m_f->glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);

    GLfloat data[]={-0.9,0.9
                    ,0.9,-0.9
                    ,-0.9,-0.9
                    ,0.9,0.9};


    m_f->glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);

    int vertexLoc =  m_program->attributeLocation("vetex");
    m_program->enableAttributeArray(vertexLoc);

    m_f->glVertexAttribPointer(vertexLoc,2,GL_FLOAT,GL_FALSE,0,(void*)(0));

    //一个VAO 管理多个VBO例子
    m_f->glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
    GLfloat color[] = {
        1,0,0,
        0,1,0,
        0,0,1,
        1,1,0
    };
    m_f->glBufferData(GL_ARRAY_BUFFER,sizeof(color),color,GL_STATIC_DRAW);
    int colorLoc = m_program->attributeLocation("color");
    m_f->glEnableVertexAttribArray(colorLoc);

    m_f->glVertexAttribPointer(colorLoc,3,GL_FLOAT,GL_FALSE,0,(void*)(0));

    //使用EBO（index buffer object IBO）例子
    uint  ebo;
    m_f->glGenBuffers(1,&ebo);
    m_f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

    GLuint indices[] ={0,1,2,0,1,3};
    m_f->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

}
