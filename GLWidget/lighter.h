#ifndef LIGHTER_H
#define LIGHTER_H

#include "baserender.h"

#include "camera.h"

class Lighter : public BaseRender
{
public:
    Lighter(QOpenGLFunctions_4_3_Core *f,QWidget *parent);
    ~Lighter();

    void  initial();
    void  resize(int w,int h);
    void  render();

protected:
   void keyPressEvent(QKeyEvent *);
   void wheelEvent(QWheelEvent *e);

   void mouseMoveEvent(QMouseEvent *);
   void mouseReleaseEvent(QMouseEvent *e);

private:
    void createProgram();

    void makeObj();

    ShaderProgram *m_lampProgram;

    Camera m_camera;
    GLuint   m_vbo,m_cubeVao,m_lightVao;

    GLint    m_cubeVertLocation,m_cubeNormalLocation,m_lightVertLocation;
    float      m_fov = 45.0f;
};

#endif // LIGHTER_H
