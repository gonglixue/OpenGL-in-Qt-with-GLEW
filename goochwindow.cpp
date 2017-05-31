#include "goochwindow.h"
#include <QSlider>

GoochWindow::GoochWindow():MyWindow()
{
    ThisGoochWidget = new QGoochGLWidget;
    glWidget = ThisGoochWidget;

    alphaSlider = new QSlider(Qt::Horizontal);
    betaSlider = new QSlider(Qt::Horizontal);
    alphaSlider->setRange(0, 10);
    betaSlider->setRange(0, 10);

    alphaLabel = new QLabel();
    alphaLabel->setText("alpha");
    betaLabel = new QLabel();
    betaLabel->setText("beta");

    connect(alphaSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setAlpha);
    connect(betaSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setBeta);
    connect(xSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setXRotation);
    connect(ySlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setYRotation);
    connect(zSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setZRotation);
    connect(lightXSlider, &QSlider::valueChanged, ThisGoochWidget, &QGoochGLWidget::setLightX);

    //alphaSlider->show();
    ctrContainer->addWidget(alphaLabel);
    ctrContainer->addWidget(alphaSlider);
    ctrContainer->addWidget(betaLabel);
    ctrContainer->addWidget(betaSlider);
    //container->addWidget(ThisGoochWidget);
    mainContainer->addLayout(ctrContainer);
    mainContainer->addWidget(ThisGoochWidget);

    setLayout(mainContainer);

    alphaSlider->setValue(5);
    betaSlider->setValue(5);

}

