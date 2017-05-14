#ifndef GOOCHWINDOW_H
#define GOOCHWINDOW_H
#include "mywindow.h"

class GoochWindow:public MyWindow
{
    Q_OBJECT
public:
    GoochWindow();
private:
    QSlider *alphaSlider;
    QSlider *betaSlider;
};

#endif // GOOCHWINDOW_H
