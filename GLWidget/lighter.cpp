#include "lighter.h"

#include <QWheelEvent>

QVector3D lightPos(1.2f, 1.0f, 2.0f);

Lighter::Lighter(QOpenGLFunctions_4_3_Core *f,QWidget *parent)
    :BaseRender(f,parent)
{
    m_camera.setCameraPos(QVector3D(0,0,5.0f));
    m_camera.setCameraFront(QVector3D(0,0,-1));
    m_camera.setCameraUp(QVector3D(0,1,0));

    m_camera.initEuler(0,-90);
}

Lighter::~Lighter()
{
    m_f->glDeleteVertexArrays(1,&m_cubeVao);
    m_f->glDeleteVertexArrays(1,&m_lightVao);
    m_f->glDeleteBuffers(1,&m_vbo);
}

void Lighter::initial()
{
    m_f->glEnable(GL_DEPTH_TEST);

    createProgram();
    makeObj();
}

void Lighter::resize(int w,int h)
{

}

void Lighter::render()
{
    m_f->glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    QMatrix4x4  model;
    QMatrix4x4  view;
    view.lookAt(m_camera.cameraPos(),m_camera.cameraPos()+m_camera.cameraFront(),m_camera.cameraUp());

    QMatrix4x4  projection;
    projection.perspective(m_fov,float(m_widget->width())/float(m_widget->height()),0.1f,100.0f);

    QMatrix4x4 normModel =  model.inverted().transposed();
    m_program->bind();
    m_program->setUniformValue("model",model);
    m_program->setUniformValue("view",view);
    m_program->setUniformValue("projection",projection);
    m_program->setUniformValue("normModel",normModel);
    m_program->setUniformValue("viewPos",m_camera.cameraPos());

    m_program->setUniformValue("objectColor",QVector3D(1.0f, 0.5f, 0.31f));
    m_program->setUniformValue("lightColor",QVector3D(1.0f, 1.0f, 1.0f));

    m_program->setUniformValue("lightPos",lightPos);
    m_program->setUniformValue("material.ambient",QVector3D(1.0f, 0.5f, 0.31f));
    m_program->setUniformValue("material.diffuse",QVector3D(1.0f, 0.5f, 0.31f));
    m_program->setUniformValue("material.specular",QVector3D(0.5f, 0.5f, 0.5f));
    m_program->setUniformValue("material.shininess", 32.0f);

    m_f->glBindVertexArray(m_cubeVao);
    m_f->glDrawArrays(GL_TRIANGLES,0,36);

    //light----------------------------------------------------
    m_lampProgram->bind();
    QMatrix4x4 model1;
    model1.translate(lightPos);
    model1.scale(0.2f);

    m_lampProgram->setUniformValue("model",model1);
    m_lampProgram->setUniformValue("view",view);
    m_lampProgram->setUniformValue("projection",projection);

    m_f->glBindVertexArray(m_lightVao);
    m_f->glDrawArrays(GL_TRIANGLES,0,36);
}

void  Lighter::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W || e->key() == Qt::Key_A || e->key() == Qt::Key_S || e->key() == Qt::Key_D)
    {
        m_camera.keyPress(e->key());
        m_widget->update();
    }
}

void Lighter::wheelEvent(QWheelEvent *e)
{
    if(m_fov>=1.0f && m_fov<=45.0f)
    {
        m_fov += e->angleDelta().y()/120;
        m_fov = m_fov<1.0f?1.0f:m_fov;
        m_fov = m_fov>45.0f?45.0f:m_fov;
        m_widget->update();
    }
}

void Lighter::mouseMoveEvent(QMouseEvent *e)
{
    m_camera.moseMove(e->pos());
    m_widget->update();
}

void Lighter::mouseReleaseEvent(QMouseEvent *e)
{
    m_camera.mouseRelease();
}

void Lighter::createProgram()
{
    m_program->loadShader(":/resources/light/vert.vert",":/resources/light/light.frag");

    m_program->bind();
    m_cubeVertLocation  = m_program->attributeLocation("Vertex");
    m_cubeNormalLocation = m_program->attributeLocation("aNormal");

    m_lampProgram = new ShaderProgram(this);
    m_lampProgram->loadShader(":/resources/light/vert.vert",":/resources/light/lamp.frag");
    m_lampProgram->bind();

    m_lightVertLocation = m_lampProgram->attributeLocation("Vertex");
    qDebug()<<"vert location:"<<m_cubeVertLocation<<m_lightVertLocation;
}

void Lighter::makeObj()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    m_f->glGenBuffers(1,&m_vbo);
    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    m_f->glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    m_f->glGenVertexArrays(1,&m_cubeVao);
    m_f->glBindVertexArray(m_cubeVao);

    m_f->glVertexAttribPointer(m_cubeVertLocation,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),0);
    m_f->glEnableVertexAttribArray(m_cubeVertLocation);

    m_f->glVertexAttribPointer(m_cubeNormalLocation,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
    m_f->glEnableVertexAttribArray(m_cubeNormalLocation);

    m_f->glGenVertexArrays(1,&m_lightVao);
    m_f->glBindVertexArray(m_lightVao);
    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_vbo);

    m_f->glVertexAttribPointer(m_lightVertLocation,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),0);
    m_f->glEnableVertexAttribArray(m_lightVertLocation);

}

