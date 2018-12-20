#ifndef BASERENDER_H
#define BASERENDER_H

#include <QOpenGLFunctions_4_3_Core>

class BaseRender
{
public:
    BaseRender(QOpenGLFunctions_4_3_Core *f);

public:
    virtual void  initial(){}
    virtual void  resize(int w,int h){}
    virtual void  render(){}

private:
    QOpenGLFunctions_4_3_Core  *m_f;
};

#endif // BASERENDER_H
