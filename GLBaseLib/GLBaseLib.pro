#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T15:58:42
#
#-------------------------------------------------

TARGET = GLBaseLib
TEMPLATE = lib

DEFINES += GLBASELIB_LIBRARY

include (../global.pri)

SOURCES += shaderprogram.cpp \
    camera.cpp

HEADERS += shaderprogram.h\
        glbaselib_global.h \
    camera.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
