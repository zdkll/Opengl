#include "glwidget.h"
#include <QApplication>

#include <QDebug>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
    w.show();

//    glm::vec4 vec(1.0,0,0,1.0);
//    glm::mat4 trans;
//    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
//    vec = trans*vec;
//    std::cout<<vec.x<<vec.y<<vec.z<<std::endl;

//    float *data = glm::value_ptr(vec);
//    for(int i=0;i<4;i++)
//        std::cout<<data[i]<<std::endl;
    return a.exec();
}
