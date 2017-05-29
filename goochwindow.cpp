#include "goochwindow.h"
#include <QSlider>

GoochWindow::GoochWindow():MyWindow()
{
    ThisGoochWidget = new QGoochGLWidget;
    glWidget = ThisGoochWidget;

    alphaSlider = new QSlider(Qt::Vertical);
    betaSlider = new QSlider(Qt::Vertical);
    alphaSlider->setRange(0, 10);
    betaSlider->setRange(0, 10);

    connect(alphaSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setAlpha);
    connect(betaSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setBeta);
    connect(xSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setXRotation);
    connect(ySlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setYRotation);
    connect(zSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setZRotation);
    connect(lightXSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setLightX);

    //alphaSlider->show();
    container->addWidget(alphaSlider);
    container->addWidget(betaSlider);
    container->addWidget(ThisGoochWidget);

    alphaSlider->setValue(5);
    betaSlider->setValue(5);

}

