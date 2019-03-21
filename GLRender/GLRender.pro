#-------------------------------------------------
#
# Project created by QtCreator 2019-03-21T10:25:25
#
#-------------------------------------------------

QT       += widgets opengl

TARGET = GLRender
TEMPLATE = lib

DEFINES += GLRENDER_LIBRARY

SOURCES += baserender.cpp

HEADERS += baserender.h\
        glrender_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
