#ifndef BASERENDER_H
#define BASERENDER_H

#include <QOpenGLFunctions_4_3_Core>
#include <QWidget>

#include <QObject>
#include <QtGui>

#include "shaderprogram.h"

class BaseRender : public QObject
{
public:
    BaseRender(QOpenGLFunctions_4_3_Core *f,QWidget *parent);

    virtual void  initial(){}
    virtual void  resize(int w,int h){}
    virtual void  render(){}

    ShaderProgram *shaderProgram(){return m_program;}

protected:
    bool eventFilter(QObject *watched, QEvent *event);

    virtual void keyPressEvent(QKeyEvent *){}
    virtual void keyReleaseEvent(QKeyEvent *){}
    virtual void mousePressEvent(QMouseEvent *){}
    virtual void mouseMoveEvent(QMouseEvent *){}
    virtual void mouseReleaseEvent(QMouseEvent *){}

    QOpenGLFunctions_4_3_Core  *m_f;
    ShaderProgram  *m_program;
    QWidget            *m_widget;
};

#endif // BASERENDER_H
