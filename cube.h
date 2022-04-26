#ifndef QCube_H
#define QCube_H

#include <QWidget>
#include<QGLWidget>
#include<QTimer>
#include<QLabel>
#include<QHBoxLayout>
#include<QGroupBox>
#include<QPushButton>
#include<QTextBrowser>
#include<QEventLoop>
#include<QMessageBox>

/**
 * @brief CubeWidget::CubeWidget
 * This is the class which manipulate everything we need.
 *
 * @author:Robert Li, Wenlin Li, Qingwen Bao, Julian Zhou, Qimeng Chao.
 * @version: 1.0 Implement the cube rotation
 * @version: 2.0 Added mess cube, reset the cube, and pages functions.
 * @version: 3.0 Added 5 cases for users to try and learn, solution provided.
 *
 */

struct Piece
{
    int color[7];
} ;

/**
 *the cube model.
 */
class QCube;

/**
 * @brief The CubeWidget class
 * UI
 */
class CubeWidget : public QWidget
{
    Q_OBJECT
public:
    CubeWidget();
    ~CubeWidget();
    void initUi();
    void setFreeze(bool value);

public slots:
    void showTutorial();
    void showInfo();
    void showCases(int index);
    void showSolutions(int c[], int num, int case_num);

protected:
    void keyPressEvent(QKeyEvent *event);

    void labelBlink(QLabel* label);
private:
    QCube* cube;

    QLabel *labelQ,*labelW,*labelE,*labelR,*labelT,*labelY;
    QLabel *labelUp,*labelDown,*labelLeft,*labelRight;
    QLabel *labelCtrl;
    QPushButton *pushButtonMess, *pushButtonRestore, *pushButtonTutorial, *pushButtonInfo;
    QPushButton *pushButtonCase1,*pushButtonCase2,*pushButtonCase3,*pushButtonCase4,*pushButtonCase5;
};

/**
 * @brief The QCube class
 * Controller.
 */
class QCube : public QGLWidget
{
    Q_OBJECT
public:
    explicit QCube(QWidget *parent=0);
    ~QCube();


    // X Y Z
    // L R: left right
    // U D: up down
    // F B: front back
    // P N: positive negative

    void turnYLP();
    void turnYLN();
    void turnYRP();
    void turnYRN();

    void turnZUP();
    void turnZUN();
    void turnZDP();
    void turnZDN();

    void turnXFP();
    void turnXFN();
    void turnXBP();
    void turnXBN();

    void updateAxis(int axis, int value);
    void resetCube();
    void messCube();
    void rotate(int opt);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintQCube(int x,int y,int z);
    void setcolor(int k);
    void scan(Piece cube[2][2][2]);
    void turnX(int n,int m);
    void turnY(int n,int m);
    void turnZ(int n,int m);
    void print();
    void keyPressEvent(QKeyEvent *event);
public slots:
    void turnx();
    void turny();
    void turnz();
private:
    bool fullscreen;

    CubeWidget* m_parent;

    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_z;
    int record;
    QTimer *timer;
    int xn,xr;
    int yn,yr;
    int zn,zr;
    char ch[1000];
    int level[1000];
    int count;
    int pre;
    Piece cube[2][2][2];
    Piece cube2[2][2][2];
    int angelx[2][2][2];
    int angely[2][2][2];
    int angelz[2][2][2];
};

#endif // QCube_H
