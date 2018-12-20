#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>

#include "shaderprogram.h"
#include "ambientlight.h"

class QOpenGLFunctions_4_3_Core;
class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);

    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();

private:
    BaseRender *m_render;
    QOpenGLFunctions_4_3_Core *m_f;

    ShaderProgram  *m_program;
};

#endif // GLWIDGET_H
