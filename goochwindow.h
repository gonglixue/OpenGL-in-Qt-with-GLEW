#ifndef GOOCHWINDOW_H
#define GOOCHWINDOW_H
#include "mywindow.h"
#include "goochglwidget.h"

class GoochWindow:public MyWindow
{
    Q_OBJECT
public:
    GoochWindow();
private:
    QSlider *alphaSlider;
    QSlider *betaSlider;

    GoochGLWidget* ThisGoochWidget;

};

#endif // GOOCHWINDOW_H
