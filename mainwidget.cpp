/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"

#include <QMouseEvent>

#include <cmath>
#include <iostream>

MainWidget::MainWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    Cube c1;     //top front left
    c1.posX = -1;
    c1.posY = 1;
    c1.posZ = -10;
    cubelist[0] = c1;

    Cube c2;
    c2.posX = 1;
    c2.posY = 1;
    c2.posZ = -10;
    cubelist[1] = c2;

    Cube c3;
    c3.posX = -1;
    c3.posY = -1;
    c3.posZ = -10;
    cubelist[2] = c3;

    Cube c4;
    c4.posX = 1;
    c4.posY = -1;
    c4.posZ = -10;
    cubelist[3] = c4;

    Cube c5;
    c5.posX = -1;
    c5.posY = 1;
    c5.posZ = -12;
    cubelist[4] = c5;

    Cube c6;
    c6.posX = 1;
    c6.posY = 1;
    c6.posZ = -12;
    cubelist[5] = c6;

    Cube c7;
    c7.posX = -1;
    c7.posY = -1;
    c7.posZ = -12;
    cubelist[6] = c7;

    Cube c8;
    c8.posX = 1;
    c8.posY = -1;
    c8.posZ = -12;
    cubelist[7] = c8;

    for(int i = 0; i<=8;i++){
        cubelist[i].wordPos = 0;
    }

}
MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}
void MainWidget::rotRight(){

    rotationAxis = (QVector3D(0,1,0)).normalized();
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, +45) * rotation;
    /**********************/
    cubelist[0].posX = cubelist[0].posX+1;
    cubelist[0].posZ = cubelist[0].posZ+1;
    cubelist[1].posX = cubelist[1].posX+1;
    cubelist[1].posZ = cubelist[1].posZ-1;
    cubelist[2].posX = cubelist[2].posX+1;
    cubelist[2].posZ = cubelist[2].posZ+1;
    cubelist[3].posX = cubelist[3].posX+1;
    cubelist[3].posZ = cubelist[3].posZ-1;
    update();
}

void MainWidget::rotUpdate(QString dir, int cubeIndex, double rotAngel){
    if(dir == "right"){
        if(cubelist[cubeIndex].wordPos+rotAngel <360){

        }



    }
}

void MainWidget::rotLeft(){

    rotationAxis = (QVector3D(0,1,0)).normalized();
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, -45) * rotation;
    /**********************/
    cubelist[0].posX = cubelist[0].posX-1;
    cubelist[0].posZ = cubelist[0].posZ-1;
    cubelist[1].posX = cubelist[1].posX-1;
    cubelist[1].posZ = cubelist[1].posZ+1;
    cubelist[2].posX = cubelist[2].posX-1;
    cubelist[2].posZ = cubelist[2].posZ-1;
    cubelist[3].posX = cubelist[3].posX-1;
    cubelist[3].posZ = cubelist[3].posZ+1;
    update();
}
void MainWidget::rotUp(){

    rotationAxis = (QVector3D(1,0,0)).normalized();
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, +45) * rotation;
    update();
}
void MainWidget::rotDown(){

    rotationAxis = (QVector3D(1,0,0)).normalized();
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, -45) * rotation;
    update();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->position());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->position()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
     qDebug()<<rotationAxis;

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 70.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    /****************************************/

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(cubelist[0].posX, cubelist[0].posY, cubelist[0].posZ);
    matrix.rotate(rotation);
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
    // Draw cube geometry
    geometries->drawCubeGeometry(&program);

    QMatrix4x4 matrix1;
    matrix1.translate(cubelist[1].posX, cubelist[1].posY, cubelist[1].posZ);
    matrix1.rotate(rotation);
    program.setUniformValue("mvp_matrix", projection * matrix1);
    geometries->drawCubeGeometry(&program);

    QMatrix4x4 matrix2;
    matrix2.translate(cubelist[2].posX, cubelist[2].posY, cubelist[2].posZ);
    matrix2.rotate(rotation);
    program.setUniformValue("mvp_matrix", projection * matrix2);
    geometries->drawCubeGeometry(&program);

    QMatrix4x4 matrix3;
    matrix3.translate(cubelist[3].posX, cubelist[3].posY, cubelist[3].posZ);
    matrix3.rotate(rotation);
    program.setUniformValue("mvp_matrix", projection * matrix3);
    geometries->drawCubeGeometry(&program);

    QMatrix4x4 matrix4;
    matrix4.translate(cubelist[4].posX, cubelist[4].posY, cubelist[4].posZ);
    matrix4.rotate(rotation);
    program.setUniformValue("mvp_matrix", projection * matrix4);
    geometries->drawCubeGeometry(&program);

    QMatrix4x4 matrix5;
    matrix5.translate(cubelist[5].posX, cubelist[5].posY, cubelist[5].posZ);
    matrix5.rotate(rotation);
    program.setUniformValue("mvp_matrix", projection * matrix5);
    geometries->drawCubeGeometry(&program);

    QMatrix4x4 matrix6;
    matrix6.translate(cubelist[6].posX, cubelist[6].posY, cubelist[6].posZ);
    matrix6.rotate(rotation);
    program.setUniformValue("mvp_matrix", projection * matrix6);
    geometries->drawCubeGeometry(&program);

    QMatrix4x4 matrix7;
    matrix7.translate(cubelist[7].posX, cubelist[7].posY, cubelist[7].posZ);
    matrix7.rotate(rotation);
    program.setUniformValue("mvp_matrix", projection * matrix7);
    geometries->drawCubeGeometry(&program);
}
