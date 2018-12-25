#include "baserender.h"


#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>


BaseRender::BaseRender(QOpenGLFunctions_4_3_Core *f,QWidget *parent)
    :QObject(parent),m_f(f),m_widget(parent),m_program(new ShaderProgram(this))
{

}

bool BaseRender::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(event->type() == QEvent::KeyPress)
            keyPressEvent(keyEvent);
        else
            keyReleaseEvent(keyEvent);
    }else if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *msEvent = static_cast<QMouseEvent *>(event);
        if(event->type() == QEvent::MouseButtonPress)
            mousePressEvent(msEvent);
        else if(event->type() == QEvent::MouseMove)
            mouseMoveEvent(msEvent);
        else if(event->type() == QEvent::MouseButtonRelease)
            mouseReleaseEvent(msEvent);
    }
    return QObject::eventFilter(watched,event);
}

