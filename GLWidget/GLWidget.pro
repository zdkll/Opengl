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

LIBS +=  -L$$LIB_PATH -lGLBaseLib  -lGLRender

INCLUDEPATH += $$ROOT_PATH/GLBaseLib \
                               $$ROOT_PATH/GLRender \
                             $$THIRDPARTY_PATH/include

THIRDPARTY_LIB_PATH =
CONFIG(debug,debug|release){
    LIBS += -L$$THIRDPARTY_PATH/lib/debug    -lassimpd
    THIRDPARTY_LIB_PATH = $$THIRDPARTY_PATH/lib/debug
}else{
    LIBS += -L$$THIRDPARTY_PATH/lib/release  -lassimp
    THIRDPARTY_LIB_PATH = $$THIRDPARTY_PATH/lib/release
}

SOURCES += main.cpp\
    ambientlight.cpp \
    texture.cpp \
    mvptrans.cpp \
    lighter.cpp \
    assimptest.cpp \
    redbook/render1_1.cpp

HEADERS  += \
    ambientlight.h \
    texture.h \
    mvptrans.h \
    publicdef.h \
    lighter.h \
    assimptest.h \
    redbook/render1_1.h

RESOURCES += \
    qrc.qrc

win32{
target.path = $$BIN_PATH
target.files = $$THIRDPARTY_LIB_PATH/*.dll
INSTALLS += target
}


