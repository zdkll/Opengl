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

INCLUDEPATH += $$ROOT_PATH/GLBaseLib \
                             $$THIRDPARTY_PATH/include

THIRDPARTY_LIB_PATH =
CONFIG(debug,debug|release){
    LIBS += $$THIRDPARTY_PATH/lib/debug    -lassimpd
    THIRDPARTY_LIB_PATH = $$THIRDPARTY_PATH/lib/debug
}else{
    LIBS += $$THIRDPARTY_PATH/lib/release  -lassimp
    THIRDPARTY_LIB_PATH = $$THIRDPARTY_PATH/lib/release
}

SOURCES += main.cpp\
        glwidget.cpp \
    baserender.cpp \
    ambientlight.cpp \
    texture.cpp \
    mvptrans.cpp \
    lighter.cpp \
    assimptest.cpp

HEADERS  += glwidget.h \
    baserender.h \
    ambientlight.h \
    texture.h \
    mvptrans.h \
    publicdef.h \
    lighter.h \
    assimptest.h

RESOURCES += \
    qrc.qrc


win32{
target.path = $$BIN_PATH
target.files = $$THIRDPARTY_LIB_PATH/*.dll
INSTALLS += target
}
