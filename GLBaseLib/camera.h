#ifndef CAMERA_H
#define CAMERA_H

#include <QPoint>
#include <QVector3D>

#include "glbaselib_global.h"

//自定义相机类
class GLBASELIBSHARED_EXPORT Camera
{
public:
    Camera();

    void initEuler(float pitch,float yaw);

    void setCameraPos(const QVector3D &cmPos){m_cameraPos = cmPos;}
    QVector3D  cameraPos() const {return m_cameraPos;}

    void setCameraFront(const QVector3D &cmFront){m_cameraFront = cmFront;}
    QVector3D  cameraFront() const {return m_cameraFront;}

    void setCameraUp(const QVector3D &cmUp){m_cameraUp = cmUp;}
    QVector3D  cameraUp() const {return m_cameraUp;}

    //鼠标移动和滚轮事件
    void keyPress(int key);
    void moseMove(const QPoint& pt);
    void mouseRelease(){firstMouse = true;}

private:
    QVector3D  m_cameraPos;  //相机位置
    QVector3D  m_cameraFront;//相对于相机位置前方
    QVector3D  m_cameraUp;//相机上方

    bool            firstMouse;
    QPoint        m_mousePt;//记录鼠标当前位置
    float            m_pitch,m_yaw;//俯仰角，偏航角（欧拉角）- 翻转角
};

#endif // CAMERA_H
