#ifndef BASERENDER_H
#define BASERENDER_H

#include <QOpenGLFunctions_4_3_Core>
#include <QWidget>

#include <QObject>
#include <QtGui>
#include <QScopedPointer>

#include "shaderprogram.h"
#include "glrender_global.h"

class GLRENDERSHARED_EXPORT BaseRender : public QObject
{
public:
    BaseRender(QWidget *parent = 0) ;
    BaseRender(QOpenGLFunctions_4_3_Core *f,QWidget *parent = 0);
    virtual ~BaseRender();

    void setWidget(QWidget *);
    void setOpenglFunctions(QOpenGLFunctions_4_3_Core *f);

    virtual void  initial(){}
    virtual void  resize(int w,int h){}
    virtual void  render(){}

    ShaderProgram *shaderProgram(){return m_program.data();}

    void update(){if(m_widget) m_widget->update();}
protected:
    bool eventFilter(QObject *watched, QEvent *event);

    virtual void keyPressEvent(QKeyEvent *){}
    virtual void keyReleaseEvent(QKeyEvent *){}
    virtual void mousePressEvent(QMouseEvent *){}
    virtual void mouseMoveEvent(QMouseEvent *){}
    virtual void mouseReleaseEvent(QMouseEvent *){}

    virtual void wheelEvent(QWheelEvent *){}

    QOpenGLFunctions_4_3_Core  *m_f;
    QScopedPointer<ShaderProgram>   m_program;
    QWidget              *m_widget;
};

#endif // BASERENDER_H
