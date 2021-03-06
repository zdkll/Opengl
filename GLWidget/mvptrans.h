﻿#ifndef MVPTRANS_H
#define MVPTRANS_H

#include <QOpenGLTexture>

#include "baserender.h"
#include "camera.h"

class MvpTrans : public BaseRender
{
public:
    MvpTrans(QOpenGLFunctions_4_3_Core *f,QWidget *parent);

    virtual void  initial();
    virtual void  resize(int w,int h);
    virtual void  render();

protected:
    void keyPressEvent(QKeyEvent *e);
    void timerEvent(QTimerEvent *e);

    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void wheelEvent(QWheelEvent *e);

private:
    void  createProgram();
    void  makeObj();

    GLuint m_Vbo;
    GLint   m_mixFacLocation,m_transLocation,m_modelLocation,m_viewLocation,m_projLocation;
    QOpenGLTexture m_texture1,m_texture2;
    GLfloat m_mixFactor;
    QMatrix4x4   m_trans;
    float             m_angle;

    Camera      m_camera;

    float  m_fov = 45.0f;
};

#endif // MVPTRANS_H
