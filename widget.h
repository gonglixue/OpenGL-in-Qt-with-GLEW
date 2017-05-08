#ifndef WIDGET_H
#define WIDGET_H

#include <gl/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "mesh.h"
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QDebug>
#include <QElapsedTimer>
#include <QPoint>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <iostream>

using namespace std;

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void LoadOBJ();
    QSize sizeHint() const;
    QString vShaderFile;
    QString fShaderFile;
    Camera camera;


public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setLightX(GLfloat light_x);
    void setLightY(GLfloat light_y);
    void setLightZ(GLfloat light_z);
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

    int screenWidth;
    int screenHeight;

    GLuint VBO;
    GLuint VAO;   

    int xRotAngle;
    int yRotAngle;
    int zRotAngle;
    QPoint mouseLastPos;

    int shaderType; //0:only color; 1:light;
    glm::vec3 objectColor;
    glm::vec3 lightColor;
    glm::vec3 lightPos;

    Mesh mesh;
};

#endif // WIDGET_H
