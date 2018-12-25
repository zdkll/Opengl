#include "glwidget.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions_4_3_Core>

#include "texture.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    m_f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    m_f->glClearColor(0,0,0,1);

    m_render = new Texture(m_f,this);

    this->installEventFilter(m_render);

    m_render->initial();
}

void GLWidget::resizeGL(int w,int h)
{
    m_f->glViewport(0,0,w,h);

    m_render->resize(w,h);
}

void GLWidget::paintGL()
{
    m_f->glClear(GL_COLOR_BUFFER_BIT);

    m_render->render();

}
