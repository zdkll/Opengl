#include "shaderprogram.h"

#include <QFile>

ShaderProgram::ShaderProgram(QObject *parent)
    :QOpenGLShaderProgram(parent)
{

}

bool ShaderProgram::loadShader(const QString& vertShaderFile,const QString& fragShaderFile)
{
    bool ok = false;

    QFile file(vertShaderFile);
    if(!file.open(QIODevice::ReadOnly))return false;
    QString content = file.readAll();
    file.close();
    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    ok = vertShader.compileSourceCode(content);
    if(!ok) return false;

    file.setFileName(fragShaderFile);
    if(!file.open(QIODevice::ReadOnly))return false;
    content = file.readAll();
    file.close();
    QOpenGLShader fragShader(QOpenGLShader::Fragment);
    ok = fragShader.compileSourceCode(content);
    if(!ok) return false;

    this->addShader(&vertShader);
    this->addShader(&fragShader);

    return this->link();
}
