#include "rubik.h"
#include "ui_rubik.h"
#include <QPainter>

Education::Education(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Education),
    image(":/small.png")
{
    ui->setupUi(this);

}

Education::~Education()
{
    delete ui;
}

void Education::paintEvent(QPaintEvent *){
    QPainter painter(this);
//    painter.drawImage((int)(100), (int)(100), image);
    painter.drawImage(200, 200, image);
}
