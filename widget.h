#ifndef WIDGET_H
#define WIDGET_H

#include <gl/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QDebug>
#include <QElapsedTimer>
#include <QPoint>

#include <iostream>

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QSize sizeHint() const;
    QString vShaderFile;
    QString fShaderFile;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent * event) override;

private:
    QOpenGLShaderProgram program;
    Camera camera;
    int screenWidth;
    int screenHeight;

    GLuint VBO;
    GLuint VAO;

    int xRotAngle;
    int yRotAngle;
    int zRotAngle;
    QPoint mouseLastPos;


};

#endif // WIDGET_H
