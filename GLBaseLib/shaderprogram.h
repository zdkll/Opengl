#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "glbaselib_global.h"

#include <QOpenGLShaderProgram>

class GLBASELIBSHARED_EXPORT ShaderProgram : public QOpenGLShaderProgram
{
public:
    ShaderProgram(QObject *parent = Q_NULLPTR);

    bool loadShader(const QString& vertShaderFile,const QString& fragShaderFile);

};


#endif // SHADERPROGRAM_H
