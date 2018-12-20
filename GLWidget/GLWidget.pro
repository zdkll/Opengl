#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T15:54:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = GLWidget
TEMPLATE = app

include (../global.pri)

LIBS +=  -L$$LIB_PATH  -lGLBaseLib

INCLUDEPATH += $$ROOT_PATH/GLBaseLib

SOURCES += main.cpp\
        glwidget.cpp \
    baserender.cpp \
    ambientlight.cpp

HEADERS  += glwidget.h \
    baserender.h \
    ambientlight.h

RESOURCES += \
    qrc.qrc
