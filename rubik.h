#ifndef RUBIK_H
#define RUBIK_H

#include <QMainWindow>

namespace Ui {
class Education;
}

class Education : public QMainWindow
{
    Q_OBJECT

public:
    explicit Education(QWidget *parent = nullptr);
    ~Education();

private:
    Ui::Education *ui;
};

#endif // RUBIK_H
