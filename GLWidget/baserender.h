#ifndef BASERENDER_H
#define BASERENDER_H

#include <QOpenGLFunctions_4_3_Core>

#include <QObject>
#include <QtGui>

#include "shaderprogram.h"

class BaseRender : public QObject
{
public:
    BaseRender(QOpenGLFunctions_4_3_Core *f,QObject *parent = 0);

    virtual void  initial(){}
    virtual void  resize(int w,int h){}
    virtual void  render(){}

    ShaderProgram *shaderProgram(){return m_program;}

protected:
    QOpenGLFunctions_4_3_Core  *m_f;

    ShaderProgram  *m_program;
};

#endif // BASERENDER_H
