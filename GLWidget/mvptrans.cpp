#include "mvptrans.h"

#define Vertex_Location  0
#define Color_Location   1
#define Texc_Location     2

#include "publicdef.h"

MvpTrans::MvpTrans(QOpenGLFunctions_4_3_Core *f,QWidget *parent)
    :BaseRender(f,parent),m_texture1(QOpenGLTexture::Target2D)
    ,m_texture2(QOpenGLTexture::Target2D),m_angle(0)
{
    m_mixFactor = 0.2;

    m_camera.initEuler(0,-90);

    m_camera.setCameraPos(QVector3D(0,0,3.0f));
    m_camera.setCameraFront(QVector3D(0,0,-1.0f));
    m_camera.setCameraUp(QVector3D(0,1.0f,0));

    this->startTimer(100);
}

void MvpTrans::initial()
{
    createProgram();

    makeObj();

    m_f->glEnable(GL_DEPTH_TEST);
}

void  MvpTrans::resize(int w,int h)
{

}

void MvpTrans::render()
{
    m_f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mat = m_trans;
    //mat.translate(QVector3D(0.5,-0.5,0));
    //QMatrix4x4 model;
    //model.rotate(m_angle,0.5,1,0);
    QMatrix4x4 view;
    //view.translate(0,0,-3.0f);

    //float radius = 10.0f;
    //float camx = sinf(m_angle*Pi/180.f)*radius;
    //float camz = cosf(m_angle*Pi/180.f)*radius;
    //view.lookAt(QVector3D(camx,0,camz),QVector3D(0,0,0),QVector3D(0,1,0));

    view.lookAt(m_camera.cameraPos(),m_camera.cameraPos() + m_camera.cameraFront()
                ,m_camera.cameraUp());

    QMatrix4x4 projection;
    projection.perspective(m_fov,float(m_widget->width())/float(m_widget->height()),0.1f,100.0f);//

    //m_f->glUniformMatrix4fv(m_transLocation,1,GL_FALSE,mat.data());
    //m_program->setUniformValue(m_modelLocation,model);
    m_program->setUniformValue(m_viewLocation,view);
    m_program->setUniformValue(m_projLocation,projection);

    m_f->glUniform1f(m_mixFacLocation,m_mixFactor);

    m_f->glEnableVertexAttribArray(Vertex_Location);
    m_f->glEnableVertexAttribArray(Color_Location);
    m_f->glEnableVertexAttribArray(Texc_Location);

    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_Vbo);
    m_f->glVertexAttribPointer(Vertex_Location,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),0);
    //m_f->glVertexAttribPointer(Color_Location,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
    m_f->glVertexAttribPointer(Texc_Location,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));

    //激活纹理单元，绑定纹理对象到激活的纹理单元
    m_f->glActiveTexture(GL_TEXTURE0);
    m_texture1.bind();
    m_f->glActiveTexture(GL_TEXTURE1);
    m_texture2.bind();

    //m_f->glDrawArrays(GL_TRIANGLES,0,36);

    //绘制10个立方体
    QVector3D cubePositions[] = {
        QVector3D( 0.0f,  0.0f,  0.0f),
        QVector3D( 2.0f,  5.0f, -15.0f),
        QVector3D(-1.5f, -2.2f, -2.5f),
        QVector3D(-3.8f, -2.0f, -12.3f),
        QVector3D( 2.4f, -0.4f, -3.5f),
        QVector3D(-1.7f,  3.0f, -7.5f),
        QVector3D( 1.3f, -2.0f, -2.5f),
        QVector3D( 1.5f,  2.0f, -2.5f),
        QVector3D( 1.5f,  0.2f, -1.5f),
        QVector3D(-1.3f,  1.0f, -1.5f)
    };
    for(int i=0;i<10;i++){
        //        QMatrix4x4 view1 = view;
        //        view1.translate(cubePositions[i].x(),cubePositions[i].y(),cubePositions[i].z());

        QMatrix4x4 model;
        model.translate(cubePositions[i].x(),cubePositions[i].y(),cubePositions[i].z());
        model.rotate(20.f*i,1.0f,0.3f,0.5f);
        //if(i%3 == 0)
        //    model.rotate(m_angle,0.5,1,0);

        m_program->setUniformValue(m_modelLocation,model);
        //m_program->setUniformValue(m_viewLocation,view1);
        m_f->glDrawArrays(GL_TRIANGLES,0,36);
    }

    m_f->glDisableVertexAttribArray(Vertex_Location);
    m_f->glDisableVertexAttribArray(Color_Location);
    m_f->glDisableVertexAttribArray(Texc_Location);
}

void MvpTrans::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up || e->key() == Qt::Key_Down){
        m_mixFactor = e->key() == Qt::Key_Up?(m_mixFactor+0.02):(m_mixFactor-0.02);
        m_mixFactor = std::min<float>(m_mixFactor,1.0);
        m_mixFactor = std::max<float>(m_mixFactor,0.0);
        m_widget->update();
    }
    if(e->key() == Qt::Key_W || e->key() == Qt::Key_A || e->key() == Qt::Key_S || e->key() == Qt::Key_D)
    {
        m_camera.keyPress(e->key());
        m_widget->update();
    }
}

void MvpTrans::timerEvent(QTimerEvent *e)
{
    m_angle += 1;
    m_widget->update();
}

void MvpTrans::mouseMoveEvent(QMouseEvent *e)
{
    m_camera.moseMove(e->pos());
    m_widget->update();
}

void MvpTrans::mouseReleaseEvent(QMouseEvent *e)
{
    m_camera.mouseRelease();
}

void MvpTrans::wheelEvent(QWheelEvent *e)
{
    if(m_fov>=1.0f && m_fov<=45.0f)
    {
        m_fov += e->angleDelta().y()/120;
        m_fov = m_fov<1.0f?1.0f:m_fov;
        m_fov = m_fov>45.0f?45.0f:m_fov;
        m_widget->update();
    }
}

void MvpTrans::createProgram()
{
    m_program->loadShader(":/resources/mvptrans/vert.vert",":/resources/mvptrans/frag.frag");

    m_program->bind();
    //设置采样器到对应纹理单元
    qDebug()<<m_program->uniformLocation("Texture1");
    qDebug()<<"model location:"<<m_program->uniformLocation("model");
    m_modelLocation = m_program->uniformLocation("model");
    m_viewLocation   = m_program->uniformLocation("view");
    m_projLocation    = m_program->uniformLocation("projection");
    m_program->setUniformValue(m_program->uniformLocation("Texture1"),0);
    m_program->setUniformValue(m_program->uniformLocation("Texture2"),1);

    m_program->bindAttributeLocation("Vertex",Vertex_Location);
    m_program->bindAttributeLocation("Color",Color_Location);
    m_program->bindAttributeLocation("Texc",Texc_Location);

    m_mixFacLocation = m_f->glGetUniformLocation(m_program->programId(),"MixFactor");
    m_transLocation    = m_f->glGetUniformLocation(m_program->programId(),"transform");
}

void MvpTrans::makeObj()
{
    //m_texture.set
    m_texture1.setData(QImage(":/resources/mvptrans/container.jpg").mirrored(),QOpenGLTexture::DontGenerateMipMaps);
    m_texture2.setData(QImage(":/resources/mvptrans/awesomeface.png").mirrored(),QOpenGLTexture::DontGenerateMipMaps);

    m_f->glBindTexture(GL_TEXTURE_2D,m_texture1.textureId());
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    m_f->glBindTexture(GL_TEXTURE_2D,m_texture2.textureId());
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    m_f->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //    float vertices[] = {
    //        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    //        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
    //        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    //        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // 左下
    //        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // 左上
    //    };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    m_f->glGenBuffers(1,&m_Vbo);
    m_f->glBindBuffer(GL_ARRAY_BUFFER,m_Vbo);
    m_f->glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
}
