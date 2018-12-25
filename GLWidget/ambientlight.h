#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "baserender.h"

class AmbientLight : public BaseRender
{
public:
    AmbientLight(QOpenGLFunctions_4_3_Core *f,QWidget *parent);

    void  initial();
    void  resize(int w,int h);
    void  render();
};

#endif // AMBIENTLIGHT_H
