#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLTexture>

#include "baserender.h"

class Texture : public BaseRender
{
public:
    Texture(QOpenGLFunctions_4_3_Core *f,QObject *parent = 0);

    virtual void  initial();
    virtual void  resize(int w,int h);
    virtual void  render();

private:
    void  createProgram();
    void  makeObj();

    GLuint m_Vbo;
    QOpenGLTexture m_texture;
};

#endif // TEXTURE_H
