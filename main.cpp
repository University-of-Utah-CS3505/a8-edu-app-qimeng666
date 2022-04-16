//#include "MainWindow.h"

//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}
#include "MainWindow.h"
#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
//    QSurfaceFormat format;
//    format.setDepthBufferSize(24);
//    QSurfaceFormat::setDefaultFormat(format);

//    app.setApplicationName("cube");
//    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
//    MainWidget widget;
//    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
