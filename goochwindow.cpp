#include "goochwindow.h"
#include <QSlider>

GoochWindow::GoochWindow():MyWindow()
{
    ThisGoochWidget = new GoochGLWidget;
    glWidget = ThisGoochWidget;

    alphaSlider = new QSlider(Qt::Vertical);
    betaSlider = new QSlider(Qt::Vertical);
    alphaSlider->setRange(0, 10);
    betaSlider->setRange(0, 10);

    connect(alphaSlider, &QSlider::valueChanged, ThisGoochWidget, &GoochGLWidget::setAlpha);
    connect(betaSlider, &QSlider::valueChanged, ThisGoochWidget, &GoochGLWidget::setBeta);
    //alphaSlider->show();
    container->addWidget(alphaSlider);
    container->addWidget(betaSlider);
    container->addWidget(ThisGoochWidget);
}

