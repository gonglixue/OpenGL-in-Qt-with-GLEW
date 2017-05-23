#ifndef GOOCHGLWIDGET_H
#define GOOCHGLWIDGET_H

#include "widget.h"

class GoochGLWidget : public Widget
{
    Q_OBJECT
public:
    GoochGLWidget();

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

private:
    GLfloat gooch_alpha;
    GLfloat gooch_beta;
    glm::vec3 coolColor;
    glm::vec3 warmColor;


};

#endif // GOOCHGLWIDGET_H
