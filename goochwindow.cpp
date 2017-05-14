#include "goochwindow.h"
#include <QSlider>

GoochWindow::GoochWindow():MyWindow()
{
    alphaSlider = new QSlider(Qt::Vertical);
    betaSlider = new QSlider(Qt::Vertical);
    alphaSlider->setRange(0, 10);
    betaSlider->setRange(0, 10);

    connect(alphaSlider, &QSlider::valueChanged, glWidget, &Widget::setAlpha);
    alphaSlider->show();
}

