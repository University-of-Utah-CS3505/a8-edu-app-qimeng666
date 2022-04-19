#include "rubik.h"
#include "ui_rubik.h"
#include <QPainter>
#include "mainwidget.h"

Education::Education(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Education)
{
    ui->setupUi(this);
    connect(ui->rotButtonRight , &QPushButton::clicked , ui->openGLWidget, &MainWidget::rotRight);
    connect(ui->rotButtonLeft , &QPushButton::clicked , ui->openGLWidget, &MainWidget::rotLeft);
    connect(ui->rotButtonUp , &QPushButton::clicked , ui->openGLWidget, &MainWidget::rotUp);
    connect(ui->rotButtonDown , &QPushButton::clicked , ui->openGLWidget, &MainWidget::rotDown);

}

Education::~Education()
{
    delete ui;
}

void Education::paintEvent(QPaintEvent *){
}
