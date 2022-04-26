#include "cube.h"
#include<GL/glu.h>
#include<QKeyEvent>
#include<QTimer>
#include<QPainter>
#include<QFile>
#include<QDebug>
#include<iostream>

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


/**
 * @brief CubeWidget::CubeWidget
 * Constructor
 */
CubeWidget::CubeWidget():
    cube(new QCube(this))
{
    initUi();
    setGeometry(400,400,960,360);
    cube->setGeometry(0,0,480,360);
    cube->resize(480,360);
    cube->show();
}

/**
 * @brief CubeWidget::CubeWidget
 * Default Constructor
 */
CubeWidget::~CubeWidget()
{

}

/**
 * @brief CubeWidget::initUi
 * Initial everything we need for UI here.
 */
void CubeWidget::initUi()
{
    this->setStyleSheet("QLabel { qproperty-alignment: AlignCenter; font: big; background-color: yellow; border: 5px solid black; } "
                        "QPushButton { alignment: center; font: big;}");
    labelCtrl = new QLabel(this);
    labelQ = new QLabel(this);
    labelW = new QLabel(this);
    labelE = new QLabel(this);
    labelR = new QLabel(this);
    labelT = new QLabel(this);
    labelY = new QLabel(this);
    labelUp = new QLabel(this);
    labelDown = new QLabel(this);
    labelLeft = new QLabel(this);
    labelRight = new QLabel(this);

    labelCtrl->setText("'");
    labelQ->setText("U");
    labelW->setText("D");
    labelE->setText("F");
    labelR->setText("B");
    labelT->setText("R");
    labelY->setText("L");

    labelUp->setText("Up");
    labelDown->setText("Down");
    labelLeft->setText("Left");
    labelRight->setText("Right");

    pushButtonMess = new QPushButton("Scramble",this);
    pushButtonRestore = new QPushButton("Reset",this);
    pushButtonTutorial = new QPushButton("Tutorial",this);
    pushButtonInfo = new QPushButton("Notice",this);

    pushButtonCase1 = new QPushButton("Practice1",this);
    pushButtonCase2 = new QPushButton("Practice2",this);
    pushButtonCase3 = new QPushButton("Practice3",this);
    pushButtonCase4 = new QPushButton("Practice4",this);
    pushButtonCase5 = new QPushButton("Practice5",this);

    // Never get focus from other access, or the view will be impacted.(Robert)
    pushButtonMess->setFocusPolicy(Qt::NoFocus);
    pushButtonRestore->setFocusPolicy(Qt::NoFocus);
    pushButtonTutorial->setFocusPolicy(Qt::NoFocus);
    pushButtonInfo->setFocusPolicy(Qt::NoFocus);
    pushButtonCase1->setFocusPolicy(Qt::NoFocus);
    pushButtonCase2->setFocusPolicy(Qt::NoFocus);
    pushButtonCase3->setFocusPolicy(Qt::NoFocus);
    pushButtonCase4->setFocusPolicy(Qt::NoFocus);
    pushButtonCase5->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout* h_layout_1 = new QHBoxLayout(this);
    h_layout_1->addWidget(labelCtrl);
    h_layout_1->addWidget(labelQ);
    h_layout_1->addWidget(labelW);
    h_layout_1->addWidget(labelE);
    h_layout_1->addWidget(labelR);
    h_layout_1->addWidget(labelT);
    h_layout_1->addWidget(labelY);


    QGroupBox *m_GroupBox_1 = new QGroupBox("Rotate",this);
    m_GroupBox_1->setGeometry(QRect(530,5,380,80));
    m_GroupBox_1->setAlignment(Qt::AlignCenter);
    m_GroupBox_1->setLayout(h_layout_1);


    QHBoxLayout* h_layout_2 = new QHBoxLayout(this);
    h_layout_2->addWidget(labelUp);
    h_layout_2->addWidget(labelDown);
    h_layout_2->addWidget(labelLeft);
    h_layout_2->addWidget(labelRight);

    QGroupBox *m_GroupBox_2 = new QGroupBox("Veiw",this);
    m_GroupBox_2->setGeometry(QRect(530,95,380,80));
    m_GroupBox_2->setAlignment(Qt::AlignCenter);
    m_GroupBox_2->setLayout(h_layout_2);

    QHBoxLayout* h_layout_3 = new QHBoxLayout(this);
    h_layout_3->addWidget(pushButtonMess);
    h_layout_3->addWidget(pushButtonRestore);
    h_layout_3->addWidget(pushButtonTutorial);
    h_layout_3->addWidget(pushButtonInfo);

    QGroupBox *m_GroupBox_3 = new QGroupBox("Options",this);
    m_GroupBox_3->setGeometry(QRect(530,185,380,80));
    m_GroupBox_3->setAlignment(Qt::AlignCenter);
    m_GroupBox_3->setLayout(h_layout_3);

    QHBoxLayout* h_layout_4 = new QHBoxLayout(this);
    h_layout_4->addWidget(pushButtonCase1);
    h_layout_4->addWidget(pushButtonCase2);
    h_layout_4->addWidget(pushButtonCase3);
    h_layout_4->addWidget(pushButtonCase4);
    h_layout_4->addWidget(pushButtonCase5);

    QGroupBox *m_GroupBox_4 = new QGroupBox("Practices",this);
    m_GroupBox_4->setGeometry(QRect(530,275,380,80));
    m_GroupBox_4->setAlignment(Qt::AlignCenter);
    m_GroupBox_4->setLayout(h_layout_4);

    // connect
    connect(pushButtonMess, &QPushButton::clicked,this,[=](){this->cube->messCube();});
    connect(pushButtonRestore, &QPushButton::clicked,this,[=](){this->cube->resetCube();});
    connect(pushButtonTutorial,&QPushButton::clicked,this,&CubeWidget::showTutorial);
    connect(pushButtonInfo,&QPushButton::clicked,this,&CubeWidget::showInfo);
    connect(pushButtonCase1,&QPushButton::clicked,this,[=](){this->showCases(1);});
    connect(pushButtonCase2,&QPushButton::clicked,this,[=](){this->showCases(2);});
    connect(pushButtonCase3,&QPushButton::clicked,this,[=](){this->showCases(3);});
    connect(pushButtonCase4,&QPushButton::clicked,this,[=](){this->showCases(4);});
    connect(pushButtonCase5,&QPushButton::clicked,this,[=](){this->showCases(5);});
}

/**
 * @brief CubeWidget::showSolutions
 * This method show the solution for the cases we providing for users.
 * @param c
 * @param num
 * @param case_num
 */
void CubeWidget::showSolutions(int c[], int num, int case_num)
{
    QString title = "Solution of Case ";
    QString ss;

    title += QString::number(case_num,10);
    for (int i=num-1;i>-1;i--)
    {
        switch (c[i]) {
        case 0: ss+="U\' ";break;
        case 1: ss+="U ";break;
        case 2: ss+="D\' ";break;
        case 3: ss+="D ";break;
        case 4: ss+="F\' ";break;
        case 5: ss+="F ";break;
        case 6: ss+="B\' ";break;
        case 7: ss+="B ";break;
        case 8: ss+="R\' ";break;
        case 9: ss+="R ";break;
        case 10: ss+="L\' ";break;
        case 11: ss+="L ";break;
        default:
            break;
        }
    }

    QWidget *msgWidget = new QWidget;
    msgWidget->setWindowTitle("Solution");
    msgWidget->setFixedSize(200,100);
    QTextBrowser* textBrowser = new QTextBrowser(msgWidget);
    textBrowser->setGeometry(0,0,200,100);
    textBrowser->append(title+"\n");
    textBrowser->append(ss);
    textBrowser->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    msgWidget->show();
}

/**
 * @brief CubeWidget::showCases
 * This method scramble the cube in our way to provide user practice problems
 * @param index
 */
void CubeWidget::showCases(int index)
{
    int case1[6] = {1,6,8,10,2,4};
    int case2[6] = {2,5,1,0,9,7};
    int case3[6] = {7,6,5,4,2,2};
    int case4[6] = {0,11,3,7,5,1};
    int case5[6] = {2,3,3,8,6,5};

    int *opt = nullptr;
    QEventLoop eventloop;

    switch (index) {
    case 1:
        opt = case1;showSolutions(case1,6,1);break;
    case 2:
        opt = case2;showSolutions(case2,6,2);break;
    case 3:
        opt = case3;showSolutions(case3,6,3);break;
    case 4:
        opt = case4;showSolutions(case4,6,4);break;
    case 5:
        opt = case5;showSolutions(case5,6,5);break;
    default:
        break;
    }
    if (opt)
    {
        cube->resetCube();
        for (int i=0;i<6;i++)
        {
            cube->rotate(opt[i]);
            QTimer::singleShot(2000, &eventloop, SLOT(quit()));
            eventloop.exec();
        }
    }
}

/**
 * @brief CubeWidget::showTutorial
 * This method show the tutorial pages for users to read.
 */
void CubeWidget::showTutorial()
{
    //set UI
    QWidget *msgWidget = new QWidget;
    msgWidget->setWindowTitle("2x2 cube Tutorial");
    msgWidget->setFixedSize(480,360);
    QTextBrowser *textBrowser = new QTextBrowser(msgWidget);
    QTextCursor text_cursor = textBrowser->textCursor();
    text_cursor.movePosition(QTextCursor::Start);
    textBrowser->setTextCursor(text_cursor);

    textBrowser->setGeometry(0,0,400,300);

    QString info = QString("<h4>Step 1: Solving the first layer</h4>"
                           "This step is identical to step 2 of the 3x3 cube solution. "
                           "Choose a color to start with (Most popular color to start with is white or yellow – In this guide I chose yellow). "
                           "Choose a corner that has this color (yellow in our case), and bring the other 3 corner pieces to it. "
                           "Make sure that you solve the corner pieces correctly in relation to each other "
                           "(also the side colors of the corner pieces should fit each other, not only the yellow. See image- right/wrong)."
                           "<br>"
                           "<img src=:/res/step1-right-wrong-example.png width=285 height=172>"
                           "<br>"
                           "There are 3 different cases to solve a corner piece to its correct position without harming the other corners:"
                           "<br>"
                           "<img src=:/res/step1-case1.png width=100 height=100>"
                           "<img src=:/res/step1-case2.png width=100 height=100>"
                           "<img src=:/res/step1-case3.png width=100 height=100>"
                           "<br>"
                           "<h4>Step 2: Orienting the last layer pieces</h4>"
                           "Flip the cube upside down (the solved layer should be on the bottom now). "
                           "In this step the goal is to orient the last layer pieces. "
                           "The result should be that the opposite color to the color we started with will be completed "
                           "(In our case: the opposite color to yellow is white). "
                           "Note that unlike the first step, here the permutation of the corners does not matter, "
                           "meaning that they don't have to be correctly solved in relation to each other (side stickers don't have to fit)."
                           "<br>"
                           "There are 7 possible cases of last layer orientations (not including the already oriented case):"
                           "<small>"
                           "(The gray color means the sticker is not the upper face color. "
                           "The bars to the sides show where the upper face color is. In our case it's white, not yellow. "
                           "It doesn't matter of course.)"
                           "</small>"
                           "<br>"
                           "<img src=:/res/OLL-1.png width=84 height=84 style=\"margin: 10px\">"
                           "<img src=:/res/OLL-2.png width=84 height=84 style=\"margin: 10px\">"
                           "<img src=:/res/OLL-3.png width=84 height=84 style=\"margin: 10px\">"
                           "<br>"
                           "<img src=:/res/OLL-4.png width=84 height=84 style=\"margin: 10px\">"
                           "<img src=:/res/OLL-5.png width=84 height=84 style=\"margin: 10px\">"
                           "<img src=:/res/OLL-6.png width=84 height=84 style=\"margin: 10px\">"
                           "<img src=:/res/OLL-7.png width=84 height=84>"
                           "<br>"
                           "<br>"
                           "It is best to learn all the 7 algorithms. However, it is possible to completely solve this step using only 1 algorithm – the first algorithm. The idea is to execute this algorithm from different angles until its suitable case shows up, then execute it one more time and solve the step. It is possible to solve all possible cases within 3 executions, or 2 if you use also its mirror algorithm (case #2)."
                           "<br>"
                           "The first algorithm orients 3 corners counter-clockwise and leaves the 4th corner intact (its mirror algorithm, case #2, does the same, but clockwise). Before executing, try to think from which angle executing this algorithm will leave only 1 oriented corner (can be done within 1 execution from all cases), than just apply the suitable algorithm (case #1 or #2). You can execute algorithm #1 twice instead of the using #2 algorithm when it's needed (in a case a clockwise rotation needed (case#2). Doing counter-clockwise twice for the corners will be just like doing a clockwise orientation, which will solve them.)"
                           "<br>"
                           "<br>"
                           "<h4>Step 3 (and last): Permuting the last layer pieces</h4>"
                           "In this step the goal is to permute the last layer pieces so they will be also correctly solved in relation to each other, and not only correctly oriented. This step is very similar to step 5 of the 3x3 solution (beginner's method) (-also the same algorithm can be applied, it is just that the one I show here permutes the corners clockwise and not counter-clockwise)."
                           "<br>"
                           "<img src=:/res/2x2-step3.png width=295 height=100>"
                           "<br>"
                           "The way to solve this method is by looking for 2 corners that are correctly permuted in relation to each other (can be easily recognized by the fact that 2 correctly solved corners in relation to each other has the same color on their mutual face. Look for the same color in 2 adjacent corners). If you don't have 2 corners that are correctly permuted, just execute the following algorithm below from any angle that you want. After that execution, 2 correctly permuted corners will show up."
                           "<br>"
                           "<img src=:/res/step3-example.png width=100 height=100>"
                           "<br>"
                           "Then:"
                           "<br>"
                           "    Do some U turns so the 2 adjacent same colors will line up with their color on the bottom layer. Rotate the cube so that this solved color will be on the right face- see image above."
                           "<br>"
                           "    Do U' once."
                           "      The effect of this move is that the front-left corner will become solved now, and the 3 other corners will require a clockwise rotation between them. This is exactly what the next algorithm does."
                           "    Execute the following algorithm: (This is the Aa-perm algorithm. l' replaced for L' because no middle layer)"
                           "<br>"
                           "<img src=:/res/PLL.png width=100 height=100>"
                           "<br>"
                           "That’s it! You have just solved the 2 by 2 Rubik's cube! Congratulations! Keep practicing on solving the first layer and learn the algorithms by heart, so you could solve the 2x2 cube without needing them written around you (They are also useful for 3x3 speedcubing!). If you didn't solve the 3x3 Rubik's cube yet, it's just about the time to start, you already have much of the basics! Congratulations!"
                           "");
    textBrowser->insertHtml(info);


    msgWidget->show();
}

/**
 * @brief CubeWidget::showInfo
 * This shows the user notice for user.
 */
void CubeWidget::showInfo()
{
    //set UI
    QWidget *msgWidget = new QWidget;
    msgWidget->setWindowTitle("User Notice");
    msgWidget->setFixedSize(400,300);
    QTextBrowser* textBrowser = new QTextBrowser(msgWidget);
    QTextCursor text_cursor = textBrowser->textCursor();
    text_cursor.movePosition(QTextCursor::Start);
    textBrowser->setTextCursor(text_cursor);

    textBrowser->setGeometry(0,0,480,360);

    QString info = QString("<h4>User Notice</h4>"
                           "This is a 2x2 rubik's cube educational app.Carefully read the tutorial pages and try to figure the cube after press scramble!!"
                           "<br>"
                           "<h5>Controls:</h5>"
                           "<br>"
                           "press Reset: set the cube to recovered cube."
                           "<br>"
                           "press Scramble: Scramble the cube."
                           "<br>"
                           "This is a keyboard-control application for rotating the cube, for user friendly, we set the key as following:"
                           "<br>"
                           "U-Q: turn the upper cube clockwisely."
                           "<br>"
                           "D-W: turn the down side of the cube clockwisely."
                           "<br>"
                           "F-E: turn the front side of the cube clockwisely."
                           "<br>"
                           "B-R: turn the back side of the cube clockwisely."
                           "<br>"
                           "R-T: turn the right side of the cube clockwisely."
                           "<br>"
                           "L-Y: turn the left side of the cube clockwisely."
                           "<br>"
                           "<br>"
                           "Add left-control key to make the rotation conterclockwisely rotate"
                           "<br>"
                           "For example: left-control+Q:turn the upper cube conterclockwisely."
                           "<br>"
                           "<br>"
                           "Up-Down-Right-Left: to change the view of the cube."
                           "<br>");

    textBrowser->insertHtml(info);

    msgWidget->show();
}

/**
 * @brief CubeWidget::labelBlink
 * set the lable's color
 * @param label
 */
void CubeWidget::labelBlink(QLabel *label)
{
    label->setStyleSheet("QLabel { qproperty-alignment: AlignCenter; font: big; background-color: red; border: 5px solid black; }");

    QTimer::singleShot(100,this,[=](){
        label->setStyleSheet(
                    "QLabel { qproperty-alignment: AlignCenter; font: big; background-color: yellow; border: 5px solid black; }");});
}


/**
 * @brief CubeWidget::keyPressEvent
 * This method controlls all the key press event we need for performing in UI.
 * @param event
 */
void CubeWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Q:
        if (event->modifiers()==Qt::ControlModifier)
        {
            cube->turnYLP(); //U'
            labelBlink(labelCtrl);
        }
        else
            cube->turnYLN(); //U
        labelBlink(labelQ);
        break;

    case Qt::Key_W:
        if (event->modifiers()==Qt::ControlModifier)
        {
            cube->turnYRP(); //D'
            labelBlink(labelCtrl);
        }
        else
            cube->turnYRN(); //D
        labelBlink(labelW);
        break;

    case Qt::Key_E:
        if (event->modifiers()==Qt::ControlModifier)
        {
            cube->turnZUP(); //F'
            labelBlink(labelCtrl);
        }
        else
            cube->turnZUN(); //F
        labelBlink(labelE);
        break;

    case Qt::Key_R:
        if (event->modifiers()==Qt::ControlModifier)
        {
            cube->turnZDP(); //B'
            labelBlink(labelCtrl);
        }
        else
            cube->turnZDN(); //B
        labelBlink(labelR);
        break;

    case Qt::Key_T:
        if (event->modifiers()==Qt::ControlModifier)
        {
            cube->turnXFP(); //R'
            labelBlink(labelCtrl);
        }
        else
            cube->turnXFN(); //R
        labelBlink(labelT);
        break;

    case Qt::Key_Y:
        if (event->modifiers()==Qt::ControlModifier)
        {
            cube->turnXBP(); //L'
            labelBlink(labelCtrl);
        }
        else
            cube->turnXBN(); //L
        labelBlink(labelY);
        break;

    case Qt::Key_Up:
        labelBlink(labelUp);
        cube->updateAxis(0,10);
        cube->updateGL();
        break;
    case Qt::Key_Down:
        labelBlink(labelDown);
        cube->updateAxis(0,-10);
        cube->updateGL();
        break;
    case Qt::Key_Left:
        labelBlink(labelLeft);
        cube->updateAxis(1,10);
        cube->updateGL();
        break;
    case Qt::Key_Right:
        labelBlink(labelRight);
        cube->updateAxis(1,-10);
        cube->updateGL();
        break;

    case Qt::Key_Escape:
        close();
    }

}

/**
 * @brief CubeWidget::setFreeze
 * This method prevernting the cube paint conflict when we rotate too fast.
 * @param value
 */
void CubeWidget::setFreeze(bool value)
{
    this->setDisabled(value);
}

/**
 * @brief QCube::QCube
 * Store the cube's value as 3d array.
 * @param parent
 */
QCube::QCube(QWidget *parent):
    QGLWidget(parent)
{
    m_parent = (CubeWidget*)parent;
    int i,j,k;
    fullscreen=false;

    m_x=0;
    m_y=0;
    m_z=0;
    xn=0;xr=0;
    yn=0;yr=0;
    zn=0;zr=0;
    for(i=0;i<2;i++)
        for (j=0;j<2;j++)
            for(k=0;k<2;k++)
            {
                angelx[i][j][k]=0;
                angely[i][j][k]=0;
                angelz[i][j][k]=0;
            }
    scan(cube);
    record=0;
    count=0;
    pre=0;
}

/**
 * @brief QCube::~QCube
 * Default constructor
 */
QCube::~QCube()
{

}

/**
 * @brief QCube::resetCube
 * This method reset the cude.
 */
void QCube::resetCube()
{
    scan(cube);
    updateGL();
}

/**
 * @brief QCube::rotate
 * rotation controller by calling the independent methods.
 * @param opt
 */
void QCube::rotate(int opt)
{
    switch (opt) {
    case 0: turnYLN();break; //U
    case 1: turnYLP();break; //U'
    case 2: turnYRN();break; //D
    case 3: turnYRP();break; //D'
    case 4: turnZUN();break; //F
    case 5: turnZUP();break; //F'
    case 6: turnZDN();break; //B
    case 7: turnZDP();break; //B'
    case 8: turnXFN();break; //R
    case 9: turnXFP();break; //R'
    case 10: turnXBN();break; //L
    case 11: turnXBP();break; //L'
    default:break;
    }
}

/**
 * @brief QCube::messCube
 * This method randomly mess the cube.
 */
void QCube::messCube()
{
    int opt;
    QEventLoop eventloop;
    m_parent->setFreeze(true);
    for (int i=0;i<10;i++)
    {
        opt = rand()%12; // 获得 0 -11 的随机数
        rotate(opt);
        QTimer::singleShot(500, &eventloop, SLOT(quit()));
        eventloop.exec();

    }
    m_parent->setFreeze(false);
}

/**
 * @brief QCube::updateAxis
 * update axis for cube.
 * @param axis
 * @param value
 */
void QCube::updateAxis(int axis, int value)
{
    switch (axis) {
    case 0 : m_x += value; break;
    case 1 : m_y += value; break;
    case 2 : m_z += value; break;
    default:
        break;
    }
}

/**
 * @brief QCube::initializeGL
 * initialize OpenGL for 3d performance.
 */
void QCube::initializeGL()
{
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0,0.3,0.3,0.0);
    glShadeModel(GL_SMOOTH);

    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

}

/**
 * @brief QCube::resizeGL
 * controll the cube rotate
 * @param w
 * @param h
 */
void QCube::resizeGL(int w, int h)
{
    glViewport(0,0,(GLint)w,(GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0,(GLfloat)w/(GLfloat)h,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * @brief QCube::paintGL
 * Controll the colors on the cube.
 */
void QCube::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    for (int i=0;i<2;i++)
        for (int j=0;j<2;j++)
            for (int k=0;k<2;k++)
            {
                paintQCube(i,j,k);
            }
}

/**
 * @brief QCube::paintQCube
 * This method make the logic for painting, and displaying the cube.
 * @param x
 * @param y
 * @param z
 */
void QCube::paintQCube(int x, int y, int z)
{
    glLoadIdentity(); //load the matrix
    glTranslatef(0.0f,0.0f,-12.0f); //multiply the current matrix and next matrix
    glRotatef(m_x,1.0f,0.0f,0.0f);
    glRotatef(m_y,0.0f,1.0f,0.0f);
    glRotatef(m_z,0.0f,0.0f,1.0f);
    glRotatef(angelx[x][y][z],1.0f,0.0f,0.0f);
    glRotatef(angely[x][y][z],0.0f,1.0f,0.0f);
    glRotatef(angelz[x][y][z],0.0f,0.0f,1.0f);
    glTranslatef(2*x-1,2*y-1,2*z-1);

    float dif=0.1;
    float fl=0.01;
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //right top(upper)
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //left top(upper)
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //left down(upper)
    glVertex3f(1.0f, 1.0f, 1.0f);                   //right down(upper)


    glVertex3f(1.0f, -1.0f, 1.0f);                  //right up(down)
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //left up(down)
    glVertex3f(-1.0f, -1.0f, -1.0f);                //left down(down)
    glVertex3f(1.0f, -1.0f, -1.0f);                 //right down(down)

    glVertex3f(1.0f, 1.0f, 1.0f);                   //right up(front)
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //left up(front)
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //left down(front)
    glVertex3f(1.0f, -1.0f, 1.0f);                  //right down(front)

    glVertex3f(1.0f, -1.0f, -1.0f);                 //right up(back)
    glVertex3f(-1.0f, -1.0f, -1.0f);                //left up(back)
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //left down(back)
    glVertex3f(1.0f, 1.0f, -1.0f);                  //right down(back)

    glVertex3f(-1.0f, 1.0f, 1.0f);                  //right up(left)
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //left up(left)
    glVertex3f(-1.0f, -1.0f, -1.0f);                //left down(left)
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //right down(left)

    glVertex3f(1.0f, 1.0f, -1.0f);                  //right up(right)
    glVertex3f(1.0f, 1.0f, 1.0f);                   //left up(right)
    glVertex3f(1.0f, -1.0f, 1.0f);                  //left down(right)
    glVertex3f(1.0f, -1.0f, -1.0f);                 //right down(right)

    glBegin(GL_QUADS);
    setcolor(cube[x][y][z].color[1]);
    glVertex3f(1.0f-dif, 1.0f+fl, -1.0f+dif);                  //right top(upper)
    glVertex3f(-1.0f+dif, 1.0f+fl, -1.0f+dif);                  //left top(upper)
    glVertex3f(-1.0f+dif, 1.0f+fl, 1.0f-dif);                  //left down(upper)
    glVertex3f(1.0f-dif, 1.0f+fl, 1.0f-dif);                   //right down(upper)


    setcolor(cube[x][y][z].color[6]);
    glVertex3f(1.0f-dif, -1.0f-fl, 1.0f-dif);                  //right up(down)
    glVertex3f(-1.0f+dif, -1.0f-fl, 1.0f-dif);                 //left top(down)
    glVertex3f(-1.0f+dif, -1.0f-fl, -1.0f+dif);                //left down(down)
    glVertex3f(1.0f-dif, -1.0f-fl, -1.0f+dif);                 //right down(down)


    setcolor(cube[x][y][z].color[3]);
    glVertex3f(1.0f-dif, 1.0f-dif, 1.0f+fl);                   //right up(front)
    glVertex3f(-1.0f+dif, 1.0f-dif, 1.0f+fl);                  //left top(front)
    glVertex3f(-1.0+dif, -1.0f+dif, 1.0f+fl);                  //left down(front)
    glVertex3f(1.0f-dif, -1.0f+dif, 1.0f+fl);                  //right down(front)

    setcolor(cube[x][y][z].color[5]);
    glVertex3f(1.0f-dif, -1.0f+dif, -1.0f-fl);                 //right up(back)
    glVertex3f(-1.0f+dif, -1.0f+dif, -1.0f-fl);                //left top(back)
    glVertex3f(-1.0f+dif, 1.0f-dif, -1.0f-fl);                 //left down(back)
    glVertex3f(1.0f-dif, 1.0f-dif, -1.0f-fl);                  //right down(back)

    setcolor(cube[x][y][z].color[2]);
    glVertex3f(-1.0f-fl, 1.0f-dif, 1.0f-dif);                  //right up(left)
    glVertex3f(-1.0f-fl, 1.0f-dif, -1.0f+dif);                 //left top(left)
    glVertex3f(-1.0f-fl, -1.0f+dif, -1.0f+dif);                //left down(left)
    glVertex3f(-1.0f-fl, -1.0f+dif, 1.0f-dif);                 //right down(left)

    setcolor(cube[x][y][z].color[4]);
    glVertex3f(1.0f+fl, 1.0f-dif, -1.0f+dif);                  //right up(right)
    glVertex3f(1.0f+fl, 1.0f-dif, 1.0f-dif);                   //left top(right)
    glVertex3f(1.0f+fl, -1.0f+dif, 1.0f-dif);                  //left down(right)
    glVertex3f(1.0f+fl, -1.0f+dif, -1.0f+dif);                 //right down(right)
    glEnd();
}


/**
 * @brief QCube::keyPressEvent
 * Key press key event controlling Qcube's logic
 * @param event
 */
void QCube::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F1:
        fullscreen=!fullscreen;
        if(fullscreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
        }
        updateGL();
        break;
    case Qt::Key_Q:
        turnYLP();
        break;
    case Qt::Key_W:
        turnYLN();
        break;
    case Qt::Key_E:
        turnYRP();
        break;
    case Qt::Key_R:
        turnYRN();
        break;

    case Qt::Key_T:
        turnZUP();
        break;
    case Qt::Key_Y:
        turnZUN();
        break;
    case Qt::Key_U:
        turnZDP();
        break;
    case Qt::Key_I:
        turnZDN();
        break;

    case Qt::Key_A:
        turnXFP();
        break;
    case Qt::Key_S:
        turnXFN();
        break;
    case Qt::Key_D:
        turnXBP();
        break;
    case Qt::Key_F:
        turnXBN();
        break;
    case Qt::Key_Up:
        m_x +=10;
        updateGL();
        break;
    case Qt::Key_Down:
        m_x -=10;
        updateGL();
        break;
    case Qt::Key_Left:
        m_y +=10;
        updateGL();
        break;
    case Qt::Key_Right:
        m_y -=10;
        updateGL();
        break;

    case Qt::Key_Escape:
        close();
    }
}

/**
 * @brief QCube::setcolor
 *
 * @param k
 */
void QCube::setcolor(int k)
{
    switch(k)
    {
    case 1: glColor3f(0.0f, 1.0f, 0.0f);                //Green
        break;
    case 2:
        glColor3f(1.0f, 0.5f, 0.0f);                    //Orange
        break;
    case 3:
        glColor3f(1.0f, 0.0f, 0.0f);                    //Red
        break;
    case 4:
        glColor3f(1.0f, 1.0f, 0.0f);                    //Yellow
        break;
    case 5:
        glColor3f(0.0f, 0.0f, 1.0f);                    //Blue
        break;
    case 6:
        glColor3f(1.0f, 1.0f, 1.0f);                    //White
        break;
    case 0:
        glColor3f(0.0f,0.0f,0.0f);                      //NUll
    }
}

/**
 * @brief QCube::scan
 * Scan the cube and set the color.
 * @param cube
 */
void QCube::scan(Piece cube[2][2][2])
{
    int i,j,k,t;
    for (i=0;i<2;i++)
        for (j=0;j<2;j++)
            for (k=0;k<2;k++)
                for(t=1;t<=6;t++)
                    cube[i][j][k].color[t]=0;
    for (i=0;i<2;i++)
        for (j=0;j<2;j++)
        {
            cube[i][j][1].color[3]=3;
        }
    for (j=0;j<2;j++)
        for (i=0;i<2;i++)
        {
            cube[i][0][1-j].color[6]=6;
        }
    for (j=0;j<2;j++)
        for (i=0;i<2;i++)
        {
            cube[1][i][1-j].color[4]=4;
        }
    for (j=0;j<2;j++)
        for (i=0;i<2;i++)
        {
            cube[1-i][1][1-j].color[1]=1;
        }
    for (j=0;j<2;j++)
        for (i=0;i<2;i++)
        {
            cube[0][1-i][1-j].color[2]=2;
        }
    for (j=0;j<2;j++)
        for (i=0;i<2;i++)
        {
            cube[1-j][i][0].color[5]=5;
        }

}

/**
 * @brief The following method are rotation method for each side.
 */


void QCube::turnYLP()
{
    yr=1;
    turnY(1,yr);
}

void QCube::turnYLN()
{
    yr=-1;
    turnY(1,yr);
}

void QCube::turnYRP()
{
    yr=1;
    turnY(0,yr);
}

void QCube::turnYRN()
{
    yr=-1;
    turnY(0,yr);
}

void QCube::turnZUP()
{
    zr=1;
    turnZ(1,zr);
}

void QCube::turnZUN()
{
    zr=-1;
    turnZ(1,zr);
}

void QCube::turnZDP()
{
    zr=1;
    turnZ(0,zr);
}

void QCube::turnZDN()
{
    zr=-1;
    turnZ(0,zr);
}

void QCube::turnXFP()
{
    xr=1;
    turnX(1,xr);
}
void QCube::turnXFN()
{
    xr=-1;
    turnX(1,xr);
}
void QCube::turnXBP()
{
    xr=1;
    turnX(0,xr);
}
void QCube::turnXBN()
{
    xr=-1;
    turnX(0,xr);
}

/**
 * @brief QCube::turnx
 * Manage the x-rotation painting, make sure everything followed.
 */
void QCube::turnx()
{
   int i,j;
    for (i=0;i<2;i++)
       for(j=0;j<2;j++)
          angelx[xn][i][j]=angelx[xn][i][j]+xr;
    updateGL();

   record +=1;
   if (record>=90)
   {
         timer->stop();
         m_parent->setFreeze(false);
         if (xr==-1)
         {
         for ( i=0;i<2;i++)
            for( j=0;j<2;j++)
               angelx[xn][i][j]=0;
         Piece layer[2][2];
             for (i=0;i<2;i++)
              for (j=0;j<2;j++)
               {
                     layer[j][1-i]=cube[xn][i][j];
                     layer[j][1-i].color[1]=cube[xn][i][j].color[3];
                     layer[j][1-i].color[3]=cube[xn][i][j].color[6];
                     layer[j][1-i].color[6]=cube[xn][i][j].color[5];
                     layer[j][1-i].color[5]=cube[xn][i][j].color[1];
                 }
             for (i=0;i<2;i++)
              for (j=0;j<2;j++)
               {
                     cube[xn][i][j]=layer[i][j];
               }
         }
         else
             for (int k=0;k<3;k++)
             {
                 for ( i=0;i<2;i++)
                    for( j=0;j<2;j++)
                       angelx[xn][i][j]=0;
                 Piece layer[2][2];
                     for (i=0;i<2;i++)
                      for (j=0;j<2;j++)
                       {
                             layer[j][1-i]=cube[xn][i][j];
                             layer[j][1-i].color[1]=cube[xn][i][j].color[3];
                             layer[j][1-i].color[3]=cube[xn][i][j].color[6];
                             layer[j][1-i].color[6]=cube[xn][i][j].color[5];
                             layer[j][1-i].color[5]=cube[xn][i][j].color[1];
                         }
                     for (i=0;i<2;i++)
                      for (j=0;j<2;j++)
                       {
                             cube[xn][i][j]=layer[i][j];
                       }
                 }
         updateGL();

    }
}

/**
 * @brief QCube::turnX
 * Set the timer prevent painting error.
 * @param n
 * @param m
 */
void QCube::turnX(int n,int m)
{
    if (m==0) xr=-1;
    record=0;
    xn=n;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(turnx()));
    m_parent->setFreeze(true);
    timer->start(1);
}


/**
 * @brief QCube::turny
 * Y-axis rotation and painting
 */
void QCube::turny()
{
    int i,j;
    for (i=0;i<2;i++)
        for(j=0;j<2;j++)
            angely[i][yn][j]=angely[i][yn][j]+yr;
    updateGL();

    record +=1;
    if (record>=90)
    {
        timer->stop();
        m_parent->setFreeze(false);
        if (yr==-1)
        {
            for ( i=0;i<2;i++)
                for( j=0;j<2;j++)
                    angely[i][yn][j]=0;
            Piece layer[2][2];
            for (i=0;i<2;i++)
                for (j=0;j<2;j++)
                {
                    layer[1-j][i]=cube[i][yn][j];
                    layer[1-j][i].color[2]=cube[i][yn][j].color[3];
                    layer[1-j][i].color[3]=cube[i][yn][j].color[4];
                    layer[1-j][i].color[4]=cube[i][yn][j].color[5];
                    layer[1-j][i].color[5]=cube[i][yn][j].color[2];
                }
            for (i=0;i<2;i++)
                for (j=0;j<2;j++)
                {
                    cube[i][yn][j]=layer[i][j];
                }
        }
        else
            for (int k=0;k<3;k++)
            {
                for ( i=0;i<2;i++)
                    for( j=0;j<2;j++)
                        angely[i][yn][j]=0;
                Piece layer[2][2];
                for (i=0;i<2;i++)
                    for (j=0;j<2;j++)
                    {
                        layer[1-j][i]=cube[i][yn][j];
                        layer[1-j][i].color[2]=cube[i][yn][j].color[3];
                        layer[1-j][i].color[3]=cube[i][yn][j].color[4];
                        layer[1-j][i].color[4]=cube[i][yn][j].color[5];
                        layer[1-j][i].color[5]=cube[i][yn][j].color[2];
                    }
                for (i=0;i<2;i++)
                    for (j=0;j<2;j++)
                    {
                        cube[i][yn][j]=layer[i][j];
                    }
            }
        updateGL();

    }
}

/**
 * @brief QCube::turnY
 * set the timer
 * @param n
 * @param m
 */
void QCube::turnY(int n,int m)
{
    if (m==0) yr=-1;
    record=0;
    yn=n;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(turny()));
    m_parent->setFreeze(true);
    timer->start(1);
}

/**
 * @brief QCube::turnz
 * The z-axis rotation.
 */
void QCube::turnz()
{
   int i,j;
    for (i=0;i<2;i++)
       for(j=0;j<2;j++)
          angelz[i][j][zn]=angelz[i][j][zn]+zr;
    updateGL();

   record +=1;
   if (record>=90)
   {
         timer->stop();
         m_parent->setFreeze(false);
         if (zr==-1)
         {
         for ( i=0;i<2;i++)
            for( j=0;j<2;j++)
               angelz[i][j][zn]=0;
         Piece layer[2][2];
             for (i=0;i<2;i++)
              for (j=0;j<2;j++)
               {
                     layer[j][1-i]=cube[i][j][zn];
                     layer[j][1-i].color[4]=cube[i][j][zn].color[1];
                     layer[j][1-i].color[1]=cube[i][j][zn].color[2];
                     layer[j][1-i].color[2]=cube[i][j][zn].color[6];
                     layer[j][1-i].color[6]=cube[i][j][zn].color[4];
                 }
             for (i=0;i<2;i++)
              for (j=0;j<2;j++)
               {
                     cube[i][j][zn]=layer[i][j];
               }
         }
         else
             for (int k=0;k<3;k++)
             {
             for ( i=0;i<2;i++)
                for( j=0;j<2;j++)
                   angelz[i][j][zn]=0;
             Piece layer[2][2];
                 for (i=0;i<2;i++)
                  for (j=0;j<2;j++)
                   {
                         layer[j][1-i]=cube[i][j][zn];
                         layer[j][1-i].color[4]=cube[i][j][zn].color[1];
                         layer[j][1-i].color[1]=cube[i][j][zn].color[2];
                         layer[j][1-i].color[2]=cube[i][j][zn].color[6];
                         layer[j][1-i].color[6]=cube[i][j][zn].color[4];
                     }
                 for (i=0;i<3;i++)
                  for (j=0;j<3;j++)
                   {
                         cube[i][j][zn]=layer[i][j];
                   }
             }
         updateGL();
    }
}

/**
 * @brief QCube::turnZ
 * preven z-axis painting error with timer.
 * @param n
 * @param m
 */
void QCube::turnZ(int n,int m)
{
    if (m==0) zr=-1;
    record=0;
    zn=n;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(turnz()));
    m_parent->setFreeze(true);
    timer->start(1);
}


/**
 * @brief QCube::print
 * Paint the code correspondingly.
 */
void QCube::print()
{
    int i,j;
    for (i=0;i<2;i++)
    {
        qDebug()<<"         ";
        for (j=0;j<2;j++)
        {
            qDebug()<<cube2[j][1][i].color[1]<<" ";
        }
        qDebug()<<endl;
    }
    qDebug()<<"||";
    for (j=0;j<2;j++)
    {
        for (i=0;i<2;i++)
        {
            qDebug()<<cube2[0][1-j][i].color[2]<<" ";
        }
    }
    qDebug()<<"||";
    for (j=0;j<2;j++)
        for (i=0;i<2;i++)
        {
            qDebug()<<cube2[i][1-j][1].color[3]<<" ";
        }
    qDebug()<<"||";
    for (j=0;j<2;j++)
        for (i=0;i<2;i++)
        {
            qDebug()<<cube2[1][1-j][1-i].color[4]<<" ";
        }
    qDebug()<<"||";
    for(j=0;j<2;j++)
        for (i=0;i<2;i++)
        {
            qDebug()<<cube2[1-i][1-j][0].color[5]<<" ";
        }
    qDebug()<<endl;
    for (j=0;j<2;j++)
    {
        qDebug()<<"        ";
        for (i=0;i<2;i++)
        {
            qDebug()<<cube2[i][0][1-j].color[6]<<" ";
        }
        qDebug()<<endl;
    }
}
