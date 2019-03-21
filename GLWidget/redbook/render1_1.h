#ifndef RENDER1_1_H
#define RENDER1_1_H

#include "baserender.h"

class Render1_1 : public BaseRender
{
public:
    Render1_1(QWidget *parent = 0);

    virtual void  initial();
    virtual void  resize(int w,int h);
    virtual void  render();

private:
    void createObj();

    GLuint  m_vao = 0;
};

#endif // RENDER1_1_H
