#include "glwidget.h"
#include <QApplication>

#include <QDebug>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include  "./redbook/render1_1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLWidget w(new Render1_1());
    w.show();

    return a.exec();
}
