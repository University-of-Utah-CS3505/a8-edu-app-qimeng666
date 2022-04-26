#include <QApplication>
#include<iostream>
#include "cube.h"
/**
 * @brief CubeWidget::CubeWidget
 * start the application.
 *
 * @author:Robert Li, Wenlin Li, Qingwen Bao, Julian Zhou, Qimeng Chao.
 * @version: 1.0 Implement the cube rotation
 * @version: 2.0 Added mess cube, reset the cube, and pages functions.
 * @version: 3.0 Added 5 cases for users to try and learn, solution provided.
 *
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QCube w;
//    w.resize(400, 300);
//    w.show();
    CubeWidget w;
    w.show();

    return app.exec();
}

