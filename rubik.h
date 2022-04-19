#ifndef RUBIK_H
#define RUBIK_H

#include <QMainWindow>
#include "mainwidget.h"
namespace Ui {
class Education;
}

class Education : public QMainWindow
{
    Q_OBJECT

public:
    explicit Education(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    ~Education();

private:
    Ui::Education *ui;
    QImage image;
    MainWidget mainWidget;
};

#endif // RUBIK_H
