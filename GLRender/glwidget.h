#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>


#include "glrender_global.h"

class BaseRender;
class QOpenGLFunctions_4_3_Core;
class GLRENDERSHARED_EXPORT GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidget(BaseRender *render,QWidget *parent = 0);

    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();

private:
    BaseRender *m_render;
    QOpenGLFunctions_4_3_Core *m_f;

};

#endif // GLWIDGET_H
