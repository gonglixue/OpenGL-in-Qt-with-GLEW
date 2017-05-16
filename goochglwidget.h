#ifndef GOOCHGLWIDGET_H
#define GOOCHGLWIDGET_H

#include "widget.h"

class GoochGLWidget : public Widget
{
    Q_OBJECT
public:
    GoochGLWidget();
    QString vShaderFile;
    QString fShaderFile;
public slots:
    void setAlpha(float alpha);
    void setBeta(float beta);
protected:
    void initializeGL();
    void paintGL();

private:
    GLfloat gooch_alpha;
    GLfloat gooch_beta;
    glm::vec3 coolColor;
    glm::vec3 warmColor;
};

#endif // GOOCHGLWIDGET_H
