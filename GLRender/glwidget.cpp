#include "glwidget.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions_4_3_Core>

#include "shaderprogram.h"
#include "baserender.h"

GLWidget::GLWidget(BaseRender *render,QWidget *parent)
    : QOpenGLWidget(parent),m_render(render)
{
    m_render->setParent(this);
    m_render->setWidget(this);
    this->installEventFilter(m_render);
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    m_f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    m_f->glClearColor(0,0,0,1);

    m_render->setOpenglFunctions(m_f);
    m_render->initial();
}

void GLWidget::resizeGL(int w,int h)
{
    m_f->glViewport(0,0,w,h);

    m_render->resize(w,h);
}

void GLWidget::paintGL()
{
    m_render->render();
}
