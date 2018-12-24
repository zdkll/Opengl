#include "baserender.h"

BaseRender::BaseRender(QOpenGLFunctions_4_3_Core *f,QObject *parent)
    :QObject(parent),m_f(f),m_program(new ShaderProgram(this))
{

}
