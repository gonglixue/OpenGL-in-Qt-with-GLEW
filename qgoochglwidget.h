#ifndef QGOOCHGLWIDGET_H
#define QGOOCHGLWIDGET_H

#include "glwidget.h"

class QGoochGLWidget : public GLWidget
{
    Q_OBJECT
public:
    QGoochGLWidget();

public slots:
    void setAlpha(float alpha);
    void setBeta(float beta);
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setLightX(GLfloat light_x);
    void setLightY(GLfloat light_y);
    void setLightZ(GLfloat light_z);

protected:
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent* event) override;

private:
    GLfloat gooch_alpha;
    GLfloat gooch_beta;
    QVector3D coolColor;
    QVector3D warmColor;

    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLBuffer EBO;

    QOpenGLShaderProgram* silhProgram;
    QString silhVShaderFile;
    QString silhFShaderFile;
    QString silhGShaderFile;
    QVector3D edgeColor;

    void setupVertexAttribs();
};

#endif // QGOOCHGLWIDGET_H
