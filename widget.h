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

#include <iostream>

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QSize sizeHint() const;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event) override;

private:
    QOpenGLShaderProgram program;
    Camera camera;
    int screenWidth;
    int screenHeight;

};

#endif // WIDGET_H
