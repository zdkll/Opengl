#-------------------------------------------------
#
# Project created by QtCreator 2019-03-21T10:25:25
#
#-------------------------------------------------

QT       += widgets opengl

TARGET = GLRender
TEMPLATE = lib

include(../global.pri)

DEFINES += GLRENDER_LIBRARY

INCLUDEPATH += $$ROOT_PATH/GLBaseLib

LIBS += -L$$LIB_PATH -lGLBaseLib

SOURCES += baserender.cpp \
    glwidget.cpp

HEADERS += baserender.h\
        glrender_global.h \
        glwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
