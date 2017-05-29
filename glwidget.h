#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QPoint>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QVector3D>
#include <QVector2D>
#include <iostream>

#include "qmesh.h"
#include "qcamera.h"
using namespace std;

void qNormalizeAngle2(int &angle);

class GLWidget:public QOpenGLWidget, protected QOpenGLFunctions
{
        Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void loadOBJ();
    QSize sizeHint() const;
    QString vShaderFile;
    QString fShaderFile;
    QCamera camera;
    void cleanup();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setLightX(GLfloat light_x);
    void setLightY(GLfloat light_y);
    void setLightZ(GLfloat light_z);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void resizeGL(int w, int h);
    //void paintGL();
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    QOpenGLShaderProgram* program;
    QVector3D objectColor;
    QVector3D lightColor;
    QVector3D lightPos;

    QMesh mesh;

    int xRotAngle;
    int yRotAngle;
    int zRotAngle;
    QPoint mouseLastPos;

    int screenWidth;
    int screenHeight;

    QMatrix4x4 projection;
};

#endif // GLWIDGET_H
