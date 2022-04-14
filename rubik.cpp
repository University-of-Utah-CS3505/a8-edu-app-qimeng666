#include "rubik.h"
#include "ui_rubik.h"

Education::Education(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Education)
{
    ui->setupUi(this);
}

Education::~Education()
{
    delete ui;
}
