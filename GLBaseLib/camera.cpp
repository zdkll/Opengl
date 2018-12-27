#include "camera.h"

#include <QKeyEvent>
#include <qmath.h>

Camera::Camera()
{
    firstMouse = true;
}

void Camera::initEuler(float pitch,float yaw)
{
    m_pitch = pitch;
    m_yaw  = yaw;
}

void Camera::keyPress(int key)
{
    float cameraSpeed = 0.05f;
    if(key == Qt::Key_W)
        m_cameraPos += m_cameraFront*cameraSpeed;
    else if(key == Qt::Key_S)
        m_cameraPos -= m_cameraFront*cameraSpeed;
    else if(key == Qt::Key_A)
        m_cameraPos -=  QVector3D::crossProduct(m_cameraFront,m_cameraUp).normalized()*cameraSpeed;
    else if(key == Qt::Key_D)
        m_cameraPos +=  QVector3D::crossProduct(m_cameraFront,m_cameraUp).normalized()*cameraSpeed;

}

void Camera::moseMove(const QPoint& pt)
{
    if(firstMouse){
        m_mousePt = pt;
        firstMouse = false;
        return;
    }

    float xoffset = pt.x() - m_mousePt.x();
    float yoffset = m_mousePt.y() - pt.y();
    m_mousePt = pt;

    xoffset *= 0.02f;
    yoffset *= 0.02f;

    m_yaw += xoffset;
    m_pitch+= yoffset;

    if(m_pitch>89.0f)
        m_pitch = 89.0f;
    if(m_pitch<-89.0f)
        m_pitch = -89.0f;

    QVector3D front;
    front.setX(cos(qDegreesToRadians(m_yaw)) * cos(qDegreesToRadians(m_pitch)));
    front.setY(sin(qDegreesToRadians(m_pitch)));
    front.setZ(sin(qDegreesToRadians(m_yaw)) * cos(qDegreesToRadians(m_pitch)));

    m_cameraFront = front.normalized();
}
