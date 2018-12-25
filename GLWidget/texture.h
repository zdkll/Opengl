#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLTexture>

#include "baserender.h"

class Texture : public BaseRender
{
public:
    Texture(QOpenGLFunctions_4_3_Core *f,QWidget *parent);

    virtual void  initial();
    virtual void  resize(int w,int h);
    virtual void  render();

protected:
   void keyPressEvent(QKeyEvent *e);

private:
    void  createProgram();
    void  makeObj();

    GLuint m_Vbo;
    GLint   m_mixFacLocation;
    QOpenGLTexture m_texture1,m_texture2;
    GLfloat m_mixFactor;
};

#endif // TEXTURE_H
