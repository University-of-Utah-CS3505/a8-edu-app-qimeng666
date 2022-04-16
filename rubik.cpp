#include "rubik.h"
#include "ui_rubik.h"
#include <QPainter>
#include "mainwidget.h"

Education::Education(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Education)
{
    ui->setupUi(this);
    MainWidget widget;
    widget.show();

}

Education::~Education()
{
    delete ui;
}

void Education::paintEvent(QPaintEvent *){
}
