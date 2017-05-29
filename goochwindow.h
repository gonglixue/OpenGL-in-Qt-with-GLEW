#ifndef GOOCHWINDOW_H
#define GOOCHWINDOW_H
#include "mywindow.h"
//#include "goochglwidget.h"
#include "qgoochglwidget.h"

class GoochWindow:public MyWindow
{
    Q_OBJECT
public:
    GoochWindow();
private:
    QSlider *alphaSlider;
    QSlider *betaSlider;

    QGoochGLWidget* ThisGoochWidget;

};

#endif // GOOCHWINDOW_H
